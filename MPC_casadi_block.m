classdef MPC_casadi_block < matlab.System
    % MPC_casadi_block Add summary here
    %
    % This template includes the minimum set of functions required
    % to define a System object.

    % Public, tunable properties
    properties

    % sampling time of internal dynamics model
    T = 0.1;

    % prediction horizon
    N = 15;           

    % states penalty
    Q = diag([3, 0, 3, 0]);

    % controls penalty
    R = 0.01;     

    % target condition
    xs = [0; 0; 0; 0];
    

    end

    % Pre-computed constants or internal states
    properties (Access = private)
    % states limit
    x_max = 0.43; % m
    x_min = -0.43;
    xd_max = 2.0; % m/s
    xd_min = -2.0;
    q_max = inf;  % rad
    q_min = -inf;
    qd_max = inf; % rad/s
    qd_min = -inf;
    u_max = 3 * 9.81;
    u_min = -3 * 9.81;

    %-----------------READ ONLY----------------------------
    m = 0.116527;     % pend mass (kg)
    M = 0.28;     % cart mass (kg)
    L = 0.1500;    % pend's length from rotational hinge to center of gravity (m)
    I = 8.7395e-04;   % moment of inertia around center of gravity (kg.m2)
    g = 9.80665;     % gravitational accel (m/s2)
    
    kd = 0.000161;   % damping const (N.s/rad)
    kdr = 0.000001; 
    kt = 150;
    Fc = 0.00040;
    %-----------------READ ONLY----------------------------
    MPC_solver
    args
    n_controls
    n_states
    end

    methods (Access = protected)
        function num = getNumInputsImpl(~)
            num = 2;
        end
        function num = getNumOutputsImpl(~)
            num = 1;
        end
        function dt1 = getOutputDataTypeImpl(~)
        	dt1 = 'double';
        end
        function dt1 = getInputDataTypeImpl(~)
        	dt1 = 'double';
        end
        function sz1 = getOutputSizeImpl(~)
        	sz1 = [1,1];
        end
        function sz1 = getInputSizeImpl(~)
        	sz1 = [1,1];
        end
        function cp1 = isInputComplexImpl(~)
        	cp1 = false;
        end
        function cp1 = isOutputComplexImpl(~)
        	cp1 = false;
        end
        function fz1 = isInputFixedSizeImpl(~)
        	fz1 = true;
        end
        function fz1 = isOutputFixedSizeImpl(~)
        	fz1 = true;
        end
        function X_d = continuous_cartpend(obj, X, u)
            x   = X(1);
            x_d = X(2);
            q   = X(3);
            q_d = X(4);
            
            X_d = [x_d;...
                   u;...
                   q_d;...
                   (obj.m*obj.g*obj.L*sin(q) - obj.m*obj.L*cos(q)*u - obj.kd*q_d - obj.kdr*q_d^2 - obj.Fc*tanh(obj.kt*q_d))/(obj.m*obj.L^2+obj.I)];
        end

        function statesNext = RK4(statesCur, controlCur, dynFunc, Ts)
            %RK4 4th-order Runge Kutta discretization 
            %   calculate next state from current state and current control
            k1 = dynFunc(statesCur, controlCur);
            k2 = dynFunc(statesCur + Ts/2*k1, controlCur);
            k3 = dynFunc(statesCur + Ts/2*k2, controlCur);
            k4 = dynFunc(statesCur + Ts*k3, controlCur);
            statesNext = statesCur +Ts/6*(k1 +2*k2 +2*k3 +k4);
        end

        function setupImpl(obj, ~, ~)
            % Perform one-time calculations, such as computing constants

            % states
            x = casadi.SX.sym('x');
            x_d = casadi.SX.sym('x_d');
            q = casadi.SX.sym('q');
            q_d = casadi.SX.sym('q_d');
            states = [x; x_d; q; q_d];
            obj.n_states = length(states);

            % controls
            u = casadi.SX.sym('u');
            controls = u;
            obj.n_controls = length(controls);

            % continuous state space sys
            X_dot = obj.continuous_cartpend(states, u);
            f_continuous = casadi.Function('f_continuous', {states, controls}, {X_dot}, ...
                {'states', 'controls'}, {'X_dot'}); % function to compute state derivative
            
            % optimization problem setup
            U = casadi.SX.sym('U', obj.n_controls, obj.N);   % decision variable (controls)
            P = casadi.SX.sym('P', obj.n_states*2);      % hold initial states and reference states
            X = casadi.SX.sym('X', obj.n_states, (obj.N+1)); % rollouts of states during prediction horizon

            % calculate objective function and dynamics constraints
            objFunc = 0;              % objective function
            g = [];               % constraints vector
            
            st = X(:, 1); % initial states
            g = [g; st - P(1:obj.n_states)]; % initial condition constraint
            
            for k = 1:obj.N 
                st = X(:,k); % current state
                con = U(:,k); % current control
                objFunc = objFunc + (st-P(obj.n_states+1:end))'*obj.Q*(st-P(obj.n_states+1:end)) + con'*obj.R*con; % calculate objective function
                st_next = X(:, k+1); % next states to optimized
                st_next_RK4 = RK4(st, con, f_continuous, obj.T);
                g = [g; st_next - st_next_RK4]; % dynamics constraints
            end

            % define solver
            optVar = [reshape(X, obj.n_states*(obj.N+1), 1); ...
                      reshape(U, obj.n_controls*obj.N, 1)]; % both X and U are optimization variable
            % define nonlinear programming problem
            nlpProb = struct();
            nlpProb.f = objFunc;
            nlpProb.x = optVar;
            nlpProb.g = g;
            nlpProb.p = P;
            
            % define solver options
            opts.ipopt.max_iter = 100;
            opts.ipopt.print_level = 0; % 0 -> 3
            opts.ipopt.acceptable_tol = 1e-8;
            opts.ipopt.acceptable_obj_change_tol = 1e-6;
            
            % define plugin options
            opts.print_time = 0; % 0, 1
            
            % define solver
            solver = casadi.nlpsol('solver', 'ipopt', nlpProb, opts);
            
            % define constraints
            args = struct;
            
            args.lbg(1:obj.n_states*(obj.N+1)) = 0; % dynamics contraints (equality constraints)
            args.ubg(1:obj.n_states*(obj.N+1)) = 0;
            
            args.lbx(1:obj.n_states:obj.n_states*(obj.N+1), 1) = obj.x_min;            % state x lower bound
            args.lbx(2:obj.n_states:obj.n_states*(obj.N+1), 1) = obj.xd_min;            % state x_d lower bound
            args.lbx(3:obj.n_states:obj.n_states*(obj.N+1), 1) = obj.q_min;          % state q lower bound
            args.lbx(4:obj.n_states:obj.n_states*(obj.N+1), 1) = obj.qd_min;          % state q_d lower bound
            
            args.ubx(1:obj.n_states:obj.n_states*(obj.N+1), 1) = obj.x_max;             % state x upper bound
            args.ubx(2:obj.n_states:obj.n_states*(obj.N+1), 1) = obj.xd_max;             % state x_d upper bound
            args.ubx(3:obj.n_states:obj.n_states*(obj.N+1), 1) = obj.q_max;           % state q upper bound
            args.ubx(4:obj.n_states:obj.n_states*(obj.N+1), 1) = obj.qd_max;           % state q_d upper bound
            
            args.lbx(obj.n_states*(obj.N+1)+1:(obj.n_states*(obj.N+1)+obj.n_controls*obj.N), 1) = obj.u_min;     % lower bound for u
            args.ubx(obj.n_states*(obj.N+1)+1:(obj.n_states*(obj.N+1)+obj.n_controls*obj.N), 1) = obj.u_max;     % upper bound for u
            
            obj.MPC_solver = solver;
            obj.args = args;
        end

        function u_opt = stepImpl(obj, X, last_u)
            % Implement algorithm. Calculate u as a function of
            % internal states. 
            tic
            X0 = repmat(X, 1, obj.N+1);       % init states variables along first prediction window
            u0 = repmat(last_u, obj.N, 1);

            args = obj.args;
            args.p = [X; obj.xs]; % params containing init state and ref state
            args.x0 = [reshape(X0', obj.n_states*(obj.N+1), 1); ...
                       reshape(u0, obj.n_controls*obj.N, 1)]; % initial value of the optimization variables
            % solution consists of both optimal control (u_opt) and optimal trajectory (X_opt)
            sol = obj.MPC_solver('x0', args.x0, 'lbx', args.lbx, 'ubx', args.ubx, ...
                'lbg', args.lbg, 'ubg', args.ubg, 'p', args.p);
            % get only opt control from the solution
            u = reshape(full(sol.x(obj.n_states*(obj.N+1)+1:end))', obj.n_controls, obj.N)';
            u_opt = full(u(1, :));
            toc
        end

        function resetImpl(obj)
            % Initialize / reset internal properties
        end
    end
end

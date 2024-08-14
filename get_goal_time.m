clear,clc,close all;
%% retrieve data
initial_angle = 0; %deg [10, 20, 30]
experiment_num = 1; %1-balance, 2-move
time_lst = [];
RSHAC_state_max_lst = [];
FC_state_max_lst = [];
LQR_state_max_lst = [];
sigma_u_lst = [];

for experiment_num=[1,2]
    for initial_angle=[0, 10, 20, 30]
        if (experiment_num==2 && initial_angle~=0) || (experiment_num==1 && initial_angle==0)
            continue
        end
        RSHAC_cutoff = load(sprintf("RSHAC_init_%d_deg_experiment_%d.mat", initial_angle, experiment_num)).out;
        FC_cutoff = load(sprintf("FC_init_%d_deg_experiment_%d.mat", initial_angle, experiment_num)).out;
        LQR_cutoff = load(sprintf("LQR_init_%d_deg_experiment_%d.mat", initial_angle, experiment_num)).out;
        
        % get cut off time
        t_RSHAC_cutOff = RSHAC_cutoff.data_RSHAC.Time(end);
        t_FC_cutOff = FC_cutoff.data_RSHAC.Time(end);
        t_LQR_cutOff = LQR_cutoff.data_RSHAC.Time(end);
        
        % get maximum state values
        RSHAC_max = max(RSHAC_cutoff.data_RSHAC.Data);
        FC_max = max(FC_cutoff.data_RSHAC.Data);
        LQR_max = max(LQR_cutoff.data_RSHAC.Data);
        
        % get sigma u
        RSHAC_sigma_u = sum(abs(RSHAC_cutoff.data_RSHAC.Data(:, end)))*0.001;
        FC_sigma_u = sum(abs(FC_cutoff.data_RSHAC.Data(:, end)))*0.001;
        LQR_sigma_u = sum(abs(LQR_cutoff.data_RSHAC.Data(:, end)))*0.001;

        % append goal time
        if experiment_num==2 && initial_angle==0
            time_lst = [time_lst; 
                t_RSHAC_cutOff-1, t_FC_cutOff-1, t_LQR_cutOff-1];
        else
            time_lst = [time_lst; 
                t_RSHAC_cutOff, t_FC_cutOff, t_LQR_cutOff];
        end
        
        % append max state values to lists
        RSHAC_state_max_lst = [RSHAC_state_max_lst;
            RSHAC_max];
        FC_state_max_lst = [FC_state_max_lst;
            FC_max];
        LQR_state_max_lst = [LQR_state_max_lst;
            LQR_max];

        % append sigma u to list
        sigma_u_lst = [sigma_u_lst;
            RSHAC_sigma_u, FC_sigma_u, LQR_sigma_u];

    end

end

%% save to file
rowNames = {'init 10deg';'init 20deg';'init 30deg';'init 0deg'};
% get time
RSHAC_goal_time = time_lst(:,1);
FC_goal_time    = time_lst(:,2);
LQR_goal_time   = time_lst(:,3);

% get delta-x, sigma-u
RSHAC_delta_x = RSHAC_state_max_lst(:, 1);
FC_delta_x = FC_state_max_lst(:, 1);
LQR_delta_x = LQR_state_max_lst(:, 1);

% get sigma u
RSHAC_sigma_u_lst = sigma_u_lst(:, 1);
FC_sigma_u_lst = sigma_u_lst(:, 2);
LQR_sigma_u_lst = sigma_u_lst(:, 3);

T = table(RSHAC_goal_time, ...
    RSHAC_delta_x, ...
    RSHAC_sigma_u_lst, ...
    FC_goal_time, ...
    FC_delta_x, ...
    FC_sigma_u_lst, ...
    LQR_goal_time, ...
    LQR_delta_x, ...
    LQR_sigma_u_lst, ...
    'RowNames',rowNames);
writetable(T,'goal_time_RSHAC.xlsx','WriteRowNames',true);
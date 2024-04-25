classdef MPC_HAC_block < matlab.System
    % untitled Add summary here
    %
    % This template includes the minimum set of functions required
    % to define a System object.

    % Public, tunable properties
    properties

    end

    % Pre-computed constants or internal states
    properties (Access = private)

    end

    methods (Access = protected)
        function setupImpl(obj)
            % Perform one-time calculations, such as computing constants
        end

        function y = stepImpl(obj,u)
            % Implement algorithm. Calculate y as a function of input u and
            % internal states.
            y = u;
        end

        function resetImpl(obj)
            % Initialize / reset internal properties
        end
    end
end

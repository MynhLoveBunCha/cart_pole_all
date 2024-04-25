function HAC(block)
% Level-2 MATLAB file S-Function for times two demo.
%   Copyright 1990-2009 The MathWorks, Inc.

  setup(block);
  
%endfunction

function setup(block)
  
  %% Register number of input and output ports
  block.NumInputPorts  = 4;
  block.NumOutputPorts = 1;

  %% Setup functional port properties to dynamically
  %% inherited.
  block.SetPreCompInpPortInfoToDynamic;
  block.SetPreCompOutPortInfoToDynamic;
 
%   block.InputPort(1).DirectFeedthrough = true;
  
  %% Set block sample time to inherited
  block.SampleTimes = [-1 0];
  
  %% Set the block simStateCompliance to default (i.e., same as a built-in block)
  block.SimStateCompliance = 'DefaultSimState';

  %% Run accelerator on TLC
  block.SetAccelRunOnTLC(true);
  
  %% Register methods
  block.RegBlockMethod('Outputs',                 @Output);  
  
%endfunction
function Output(block)
% xac dinh khoang gia tri thuc
q_kt =[-0.3 0.3];
q_dot_kt =[-1 1];
x_kt = [-3 3];
x_dot_kt =[-3 3];
u_kt = [-40 40];
% xac dinh cong vao cho cac bien
x = block.InputPort(1).Data;
x_dot = block.InputPort(2).Data;
q = block.InputPort(3).Data;
q_dot = block.InputPort(4).Data;

% xac dinh gia tri ngu nghia cho dau vao
qs = (q-q_kt(1))/(q_kt(2)-q_kt(1));
q_dots = (q_dot-q_dot_kt(1))/(q_dot_kt(2)-q_dot_kt(1));
xs = (x-x_kt(1))/(x_kt(2)-x_kt(1));
x_dots = (x_dot-x_dot_kt(1))/(x_dot_kt(2)-x_dot_kt(1));
% su dung luat prod hop thanh
x_star=qs*q_dots*xs*x_dots;%*Ws;
% noi suy ngu nghia dau ra
us_out = Interpolation(x_star);
% giai nghia dau ra
u_out = us_out*(u_kt(2)-u_kt(1))+u_kt(1);
%Gui ra OutPort
block.OutputPort(1).Data = u_out;  
%endfunction
%  function interpolation
function y_star = Interpolation(x_star)
x = [0 0.00390625 0.0078125	0.01171875 0.015625	0.0234375 0.03125	0.03515625	0.046875	0.0625	0.0703125	0.09375	0.10546875	0.140625	0.2109375	0.31640625];
% y =[0 0.18	0.18	0.3	0.3	0.38	0.38	0.5	0.5	0.5	0.62	0.62	0.7	0.7	0.82	0.82];
y = [0 0.15	0.15	0.25	0.25	0.375	0.375	0.5	0.5	0.5	0.625	0.625	0.75	0.75	0.825	0.825];

y_star = interp1(x,y, x_star, 'spline');


function plotHandles = drawCartPole(time,pos,extents,p,plotHandles)
% drawCartPole(time,pos,extents,p)
%
% INPUTS:
%   time = [scalar] = current time in the simulation
%   pos = [4, 1] = [x1;y1;x2;y2]; = position of [cart; pole]
%   extents = [xLow, xUpp, yLow, yUpp] = boundary of the draw window
%
% OUTPUTS:
%   --> A pretty drawing of a cart-pole
%

% Make plot objects global so that they don't get erased
cartColor = [0.2, 0.7, 0.2];   % [R, G, B]
poleColor = [0.3, 0.2, 0.7];

%%%% Unpack the positions:
x1 = pos(1);
y1 = pos(2);
x2 = pos(3);
y2 = pos(4);

%%%% Unpack the positions:
railHandle = plotHandles.railHandle;
cartHandle = plotHandles.cartHandle;
poleHandle = plotHandles.poleHandle;

% Title and simulation time:
title(sprintf('t = %2.2f%',time));


% Draw the rail that the cart-pole travels on
if isempty(railHandle)
    railHandle = plot(extents(1:2),[-p.h/2,-p.h/2],'k-','LineWidth',2);
end

% Draw the cart:
if isempty(cartHandle)
    cartHandle = rectangle(...
        'Position',[x1-0.5*p.w, y1-0.5*p.h, p.w, p.h],...
        'LineWidth',2,...
        'FaceColor',cartColor,...
        'EdgeColor',0.5*cartColor);  %Darker version of color
else
    set(cartHandle,...
    'Position',[x1-0.5*p.w, y1-0.5*p.h, p.w, p.h]);
end


% Draw the pole:
if isempty(poleHandle)
    poleHandle = plot([x1,x2], [y1, y2],...
        'LineWidth',4,...
        'Color',0.8*poleColor);
else
    set(poleHandle,...
    'xData',[x1,x2],...
    'yData',[y1,y2]);
end

% Format the axis so things look right:
axis equal; axis(extents); axis on;      %  <-- Order is important here

% Push the draw commands through the plot buffer
drawnow;

plotHandles.railHandle = railHandle;
plotHandles.cartHandle = cartHandle;
plotHandles.poleHandle = poleHandle;
end
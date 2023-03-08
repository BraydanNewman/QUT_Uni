function [optDist, optx, opty] = minMaxDistance(sx, sy, snames, event)
% [OPTIMAL_DISTANCE, OPTIMAL_X OPTIMAL_Y] = minMaxDistance(SX, SY, NAMES, EVENT)
% finds the optimal destination that minimises the maximum distance for
% either 'BBQ' or 'coffee'

s = [sx(:) sy(:)];

% get the size of the arrays
m = size(s,1);

if strcmpi(event, 'bbq')
    d = s;
    n = m;
elseif strcmpi(event, 'coffee')
    f = @(x) max(sqrt((s(:,1) - x(1)).^2 + (s(:,2) - x(2)).^2));
    d = fminsearch(f, [0 0]);
    n = 1;
else
    error('event should be either BBQ or coffee')
end

% allocate memory for distances
L = zeros(m,n);

% calculate Euclidean distances
for j = 1:n
    L(:,j) = sqrt( sum( bsxfun(@minus,s,d(j,:)).^2 ,2) );
end

% calculate maximum distance from all sources to each destination
T = max(L,[],1);

% find the minimum distance
[optDist, optDest] = min(T);

% produce figure

fontsize = 12;

% sources
figure
plot(s(:,1), s(:,2), 'bo')
axis equal
hold on

text(s(:,1), s(:,2), snames, 'FontSize', fontsize, ...
    'VerticalAlignment', 'top', 'HorizontalAlignment', 'left');

if ~isequal(s,d)
    
    % destination
    plot(d(:,1), d(:,2), 'gs')
    
end

% edges
for i = 1:m
    plot([s(i,1), d(optDest,1)], [s(i,2), d(optDest,2)], 'k');
end

% distances
for i = 1:m
    distance = sqrt(sum((s(i,:) - d(optDest,:)).^2));
    midpoint = (s(i,:) + d(optDest,:)) / 2;
    if distance ~= 0
        text(midpoint(1), midpoint(2), num2str(distance, '%1.2f'), 'FontSize', fontsize)
    end
end

% title
title_str = sprintf('Maximum distance travelled = %1.2f', optDist);
if strcmpi(event, 'bbq')
    title_str = [sprintf('%s hosts the barbecue\n', snames{optDest}) title_str];
else
    title_str = [sprintf('Coffee at location (%1.2f, %1.2f)\n', d(1), d(2)) title_str];
end
title(title_str, 'FontSize', fontsize)
set(gca, 'FontSize', fontsize)

% expand axis a bit
ax = axis;
axis(1.2*ax);

optx = d(optDest,1);
opty = d(optDest,2);


end % function minMaxDistance
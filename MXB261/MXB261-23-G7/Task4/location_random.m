%% 10% of food and parasite density, f1 = 3, f2=0.1,f3=100,
[totalFoodCounts1,totalParasiteCounts1] = randomlocation(15,0.1,0.1,3,0.1,100,false);
%% 10% OF food and parasite density, f1 = 10, f=0.01, f3 = 300
[totalFoodCounts2,totalParasiteCounts2] = randomlocation(15,0.1,0.1,10,0.01,300,false);
%% 40% of food and parasite density, f1= 3, f2 = 0.1, f3= 100
[totalFoodCounts3,totalParasiteCounts3] = randomlocation(15,0.4,0.4,3,0.1,100,false);
%% 40% of food and parasite density, f1= 10, f2 = 0.01, f3= 300
[totalFoodCounts4,totalParasiteCounts4] = randomlocation(15,0.4,0.4,10,0.01,300,false);
%%
% Create a figure
figure;

% Create subplots in a 2x2 grid
subplot(2, 2, 1);
plot(totalFoodCounts1(1:end-1),'g');
hold on
plot(totalParasiteCounts1(1:end-1),'r');
hold off
title('10% Density with first parameter regime');
xlabel('Steps')
ylabel('Population')
legend('Food','Parasite')
xlim([0 70])

subplot(2, 2, 2);
plot(totalFoodCounts2(1:end-1),'g');
hold on
plot(totalParasiteCounts2(1:end-1),'r');
hold off
title('10% Density with second parameter regime');
xlabel('Steps')
ylabel('Population')
legend('Food','Parasite')
xlim([0 70])

subplot(2, 2, 3);
plot(totalFoodCounts3(1:end-1),'g');
hold on
plot(totalParasiteCounts3(1:end-1),'r');
hold off
title('40% Density with first parameter regime','Position');
xlabel('Steps')
ylabel('Population')
legend('Food','Parasite')
xlim([0 70])

subplot(2, 2, 4);
plot(totalFoodCounts4(1:end-1),'g');
hold on
plot(totalParasiteCounts4(1:end-1),'r');
hold off
title(' 40% Density with second parameter regime','Position');
xlabel('Steps')
ylabel('Population')
legend('Food','Parasite')
xlim([0 70])
% Create a big title for the entire figure
bigTitle = sgtitle('Randomised Location of Food Requiremnt');
% Adjust the title properties, such as font size and position
bigTitle.FontSize = 15;

%% Function
function[totalFoodCounts,totalParasiteCounts] = randomlocation(numIterations,initialFoodDensity,initialParasiteDensity,f1,f2,f3,createVideo)
% Define grid size
gridSize = 200;

% Initialize the grid  
grid = cell(gridSize, gridSize);
gridAges = zeros(gridSize, gridSize);

% Calculate the total number of cells in the grid
totalCells = gridSize * gridSize;

% Determine the initial population of F and P based on population densities
% initialFoodDensity = 0.10; % 10% initial food density
% initialParasiteDensity = 0.10; % 10% initial parasite density

% Calculate the number of initial food agents and parasites
numInitialFood = round(totalCells * initialFoodDensity);
numInitialParasites = round(totalCells * initialParasiteDensity);

% Randomly place the initial populations of F and P

for i = 1:numInitialParasites
    x = randi(gridSize);
    y = randi(gridSize);
    while ~isempty(grid{x, y})
        x = randi(gridSize);
        y = randi(gridSize);
    end
    grid{x, y} = 'P';
end
for i = 1:numInitialFood
    x = randi(gridSize);
    y = randi(gridSize);
    while ~isempty(grid{x, y})
        x = randi(gridSize);
        y = randi(gridSize);
    end
    grid{x, y} = 'F';
end

% Define movement directions (N, S, E, W)
directions = [0, 1; 0, -1; 1, 0; -1, 0];

% Create a figure for the animation
figure;
colormap('gray'); % Set the colormap to grayscale

% Define colors for F and P
colorF = [0, 1, 0]; % Green color for F
colorP = [1, 0, 0]; % Red color for P


frameRate = 0.1; 
 % Create a VideoWriter object (if requested)
    if createVideo
        if f1 ==3 && initialFoodDensity == 0.1
            videoFileName = 'randomised food agent with 10% Density with first input parameter.avi';
            videoObj = VideoWriter(videoFileName, 'Motion JPEG AVI');
            videoObj.FrameRate = 10; % Adjust the frame rate as needed
            open(videoObj);
        elseif f1 ==10 && initialFoodDensity == 0.1
            videoFileName = 'randomised food agent with 10% Density with second input parameter.avi';
            videoObj = VideoWriter(videoFileName, 'Motion JPEG AVI');
            videoObj.FrameRate = 10; % Adjust the frame rate as needed
            open(videoObj);
         elseif f1 ==3 && initialFoodDensity == 0.4
            videoFileName = 'randomised food agent with 40% Density with first input parameter.avi';
            videoObj = VideoWriter(videoFileName, 'Motion JPEG AVI');
            videoObj.FrameRate = 10; % Adjust the frame rate as needed
            open(videoObj);
         elseif f1 ==10 && initialFoodDensity == 0.4
            videoFileName = 'randomised food agent with 40% Density with second input parameter.avi';
            videoObj = VideoWriter(videoFileName, 'Motion JPEG AVI');
            videoObj.FrameRate = 10; % Adjust the frame rate as needed
            open(videoObj);
            
        end

    end


% Initialize arrays to track total food and parasite counts over time
totalFoodCounts = zeros(1, numIterations+1);
totalParasiteCounts = zeros(1, numIterations+1);

for iteration = 1:numIterations

    totalFoodCounts(iteration) = sum(sum(strcmp(grid, 'F')));
    totalParasiteCounts(iteration) = sum(sum(strcmp(grid, 'P')));
    % Shuffle the order of parasites to randomize their movement
    parasiteIndices = find(strcmp(grid, 'P'));
    randomOrder = parasiteIndices(randperm(length(parasiteIndices)));
    
    % Move parasites
    for idx = 1:length(randomOrder)
        [x, y] = ind2sub([gridSize, gridSize], randomOrder(idx));
        
        % Randomly shuffle the directions
        shuffledDirections = directions(randperm(4), :);
        
            % Check each direction
            for d = 1:4
                newX = x + shuffledDirections(d, 1);
                newY = y + shuffledDirections(d, 2);

                % Check if the move is within boundaries
                if newX >= 1 && newX <= gridSize && newY >= 1 && newY <= gridSize
                    % Check if the new cell is empty
                    if isempty(grid{newX, newY})
                        grid{newX, newY} = 'P';
                        gridAges(newX, newY) = gridAges(x, y) + 1;  % Increment age
                        grid{x, y} = [];
                        gridAges(x, y) = 0;
                        break; % Move successful
                    elseif strcmp(grid{newX, newY}, 'F')
                        % Consume food and give birth
                        grid{newX, newY} = 'P';
                        gridAges(newX, newY) = gridAges(x, y) + 1;  % Increment age
                        % Place a new parasite in the original cell with age 0
%                         while ~isempty(grid{x, y})
%                             x = randi(gridSize);
%                             y = randi(gridSize);
%                         end
                        grid{x, y} = 'P';
                            gridAges(x, y) = 0;
                        break;
                    end
                end
            end
        end

        % Conditions (b) and (c)
        % Check parasites for death
        parasitesToRemove = [];
        for idx = 1:length(randomOrder)
            [x, y] = ind2sub([gridSize, gridSize], randomOrder(idx));

            % Check if the parasite has reached its lifespan (with age >= f1)
            if gridAges(x, y) >= f1
                parasitesToRemove(end+1) = randomOrder(idx);
            end
        end

        % Remove dead parasites and their ages
        for idx = parasitesToRemove
            [x, y] = ind2sub([gridSize, gridSize], idx);
            grid{x, y} = [];
            gridAges(x, y) = 0;  % Reset age
        end
    
    % Check food agents for death
    for x = 1:gridSize
        for y = 1:gridSize
            if strcmp(grid{x, y}, 'F')
                % Generate a random number for each food agent
                if rand() <= f2
                    grid{x, y} = []; % Remove the food agent
                end
            end
        end
    end
    
    % Condition (d)
    % Generate f3 new food agents and place them randomly in empty cells
    if iteration <= f3
    for i = 1:f3
        x = randi(gridSize);
        y = randi(gridSize);
        while ~isempty(grid{x, y})
            x = randi(gridSize);
            y = randi(gridSize);
        end
        grid{x, y} = 'F';
    end
    end

    % Create an RGB image for the current state of the grid
    imageRGB = zeros(gridSize, gridSize, 3);
    
    % Populate the image with colors based on the grid contents
    for x = 1:gridSize
        for y = 1:gridSize
            if isempty(grid{x, y})
                % Empty cell
                imageRGB(x, y, :) = [1, 1, 1]; % White color for empty cells
            elseif strcmp(grid{x, y}, 'F')
                % Food cell
                imageRGB(x, y, :) = colorF;
            elseif strcmp(grid{x, y}, 'P')
                % Parasite cell
                imageRGB(x, y, :) = colorP;
            end
        end
    end
    
    % Display the RGB image
    scale_x = [0 200];
    scale_y = [200 0];
    imagesc(scale_x, scale_y, imageRGB);
    title('Annimation of agent base model for first parameter regimes')
    % Pause to control frame rate
    pause(frameRate);

        % Write frames to the video (if requested)
        if createVideo
            writeVideo(videoObj, im2frame(imageRGB));
        end
    end

    % Close the video file (if requested)
    if createVideo
        close(videoObj);
    end
end




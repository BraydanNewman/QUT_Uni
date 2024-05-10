%% 10% of food and parasite density, f1 = 3, f2=0.1,f3=100,
[totalFoodCounts1,totalParasiteCounts1] = localisedlocation(13,0.1,0.1,3,0.1,100,false);
%% 10% OF food and parasite density, f1 = 10, f=0.01, f3 = 300
[totalFoodCounts2,totalParasiteCounts2] = localisedlocation(13,0.1,0.1,10,0.01,300,false);
%% 40% of food and parasite density, f1= 3, f2 = 0.1, f3= 100
[totalFoodCounts3,totalParasiteCounts3] = localisedlocation1(13,0.4,0.4,3,0.1,100,false);
%% 40% of food and parasite density, f1= 10, f2 = 0.01, f3= 300
[totalFoodCounts4,totalParasiteCounts4] = localisedlocation1(13,0.4,0.4,10,0.01,300,false);
%% Figrue
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

subplot(2, 2, 2);
plot(totalFoodCounts2(1:end-1),'g');
hold on
plot(totalParasiteCounts2(1:end-1),'r');
hold off
title('10% Density with second parameter regime');
xlabel('Steps')
ylabel('Population')
legend('Food','Parasite')

subplot(2, 2, 3);
plot(totalFoodCounts3(1:end-1),'g');
hold on
plot(totalParasiteCounts3(1:end-1),'r');
hold off
title('40% Density with first parameter regime','Position');
xlabel('Steps')
ylabel('Population')
legend('Food','Parasite')

subplot(2, 2, 4);
plot(totalFoodCounts4(1:end-1),'g');
hold on
plot(totalParasiteCounts4(1:end-1),'r');
hold off
title(' 40% Density with second parameter regime','Position');
xlabel('Steps')
ylabel('Population')
legend('Food','Parasite')
% Create a big title for the entire figure
bigTitle = sgtitle('Localised Location of Food Requiremnt');
% Adjust the title properties, such as font size and position
bigTitle.FontSize = 15;

%% Function 1
function [totalFoodCounts, totalParasiteCounts] = localisedlocation(numIterations, initialFoodDensity, initialParasiteDensity, f1, f2, f3, createVideo)
     % Define grid size
    gridSize = 200;

    % Initialize the grid with structure to hold parasites and their ages
    grid = cell(gridSize, gridSize);
    gridAges = zeros(gridSize, gridSize);

    % Calculate the total number of cells in the grid
    totalCells = gridSize * gridSize;

    % Set the centers and radius for the circular areas
    centers = [50, 50; 150, 150];
    radius = 27;

    % Initialize a list to store available positions within the circles
    availablePositions = [];

    % Calculate the number of initial food agents and parasites
    numInitialFood = round(initialFoodDensity * totalCells);
    numInitialParasites = round(initialParasiteDensity * totalCells);

    % Loop through each center
    for centerIndex = 1:size(centers, 1)
        xCenter = centers(centerIndex, 1);
        yCenter = centers(centerIndex, 2);

        % Create a grid of possible positions within the circle
        [xGrid, yGrid] = meshgrid(1:gridSize, 1:gridSize);

        % Calculate distances from the center to each position
        distances = sqrt((xGrid - xCenter).^2 + (yGrid - yCenter).^2);
        % Find available positions inside the circle and not already occupied
        for x = 1:gridSize
            for y = 1:gridSize
                if distances(x, y) <= radius && isempty(grid{x, y})
                    availablePositions = [availablePositions; x, y];
                end
            end
        end
    end

    % Shuffle the available positions
    shuffledPositions = availablePositions(randperm(size(availablePositions, 1)), :);

    % Calculate the number of positions to place based on desired density
    numPositionsToPlace = min(2 * numInitialFood, size(shuffledPositions, 1)); % Multiply by 2 for two centers

    % Place food in the available positions
    for i = 1:numPositionsToPlace
        x = shuffledPositions(i, 1);
        y = shuffledPositions(i, 2);
        grid{x, y} = 'F';
    end

    % Check if there are more food particles than required
    if numPositionsToPlace > 4000
        % Calculate the excess food particles
        excessFood = numPositionsToPlace - 4000;

        % Find the indices of food particles and shuffle them
        foodIndices = find(strcmp(grid, 'F'));
        shuffledFoodIndices = foodIndices(randperm(length(foodIndices)));

        % Remove the excess food particles up to the minimum of excessFood and the number of available indices
        for i = 1:min(excessFood, length(shuffledFoodIndices))
            [x, y] = ind2sub([gridSize, gridSize], shuffledFoodIndices(i));
            grid{x, y} = []; % Remove the food particle
        end
    end

    % Randomly place the initial populations of P (parasites)
    for i = 1:numInitialParasites
        x = randi(gridSize);
        y = randi(gridSize);
        while ~isempty(grid{x, y})
            x = randi(gridSize);
            y = randi(gridSize);
        end
        grid{x, y} = 'P';
        gridAges(x, y) = 0;  % New parasite's age starts at 0
    end

    % Define movement directions (N, S, E, W)
    directions = [-1, 0; 1, 0; 0, -1; 0, 1];

    % Define colors for F and P
    colorF = [0, 1, 0]; % Green color for F
    colorP = [1, 0, 0]; % Red color for P

    % Initialize arrays to track total food and parasite counts over time
    totalFoodCounts = zeros(1, numIterations + 1);
    totalParasiteCounts = zeros(1, numIterations + 1);

    % Number of iterations and delay for animation
    animationDelay = 0.2; % Adjust the delay between frames (in seconds)

    % Create a VideoWriter object (if requested)
    if createVideo
        if f1 == 3
            videoFileName = 'localised_food_agent_with_10pct_density_first_input_parameter.avi';
            videoObj = VideoWriter(videoFileName, 'Motion JPEG AVI');
            videoObj.FrameRate = 10; % Adjust the frame rate as needed
            open(videoObj);
        else
            videoFileName = 'localised_food_agent_with_10pct_density_second_input_parameter.avi';
            videoObj = VideoWriter(videoFileName, 'Motion JPEG AVI');
            videoObj.FrameRate = 10; % Adjust the frame rate as needed
            open(videoObj);
        end
    end

    % Create a figure for the animation (if requested)
    if createVideo
        figure;
    end

    for iteration = 1:numIterations
        % Update the total food and parasite counts for this iteration
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
                % Randomly choose one of the food center locations
                centerIndex = randi(size(centers, 1));
                xCenter = centers(centerIndex, 1);
                yCenter = centers(centerIndex, 2);

                % Generate random coordinates around the chosen center
                x = randi([xCenter - radius, xCenter + radius]);
                y = randi([yCenter - radius, yCenter + radius]);

                % Ensure that the coordinates are within the grid boundaries
                x = max(1, min(x, gridSize));
                y = max(1, min(y, gridSize));

                % Check if the cell is empty
                if isempty(grid{x, y})
                    grid{x, y} = 'F';
                end
            end
        end

        % Create the RGB image
        imageRGB = zeros(gridSize, gridSize, 3);
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
        scale_y = [0 200];
        imagesc(scale_x, scale_y, imageRGB);
        title('Annimation of agent-based model for first parameter regime')
        % Pause to create an animation effect
        pause(animationDelay);

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


%% Function 2
function[totalFoodCounts,totalParasiteCounts] = localisedlocation1(numIterations,initialFoodDensity,initialParasiteDensity,f1,f2,f3,createVideo)
 % Define grid size
    gridSize = 200;

    % Initialize the grid with structure to hold parasites and their ages
    grid = cell(gridSize, gridSize);
    gridAges = zeros(gridSize, gridSize);

    % Calculate the total number of cells in the grid
    totalCells = gridSize * gridSize;

    % Set the centers and radius for the circular areas
    centers = [50, 50; 150, 150];
    radius = 51;

    % Initialize a list to store available positions within the circles
    availablePositions = [];

    % Calculate the number of initial food agents and parasites
    numInitialFood = round(initialFoodDensity * totalCells);
    numInitialParasites = round(initialParasiteDensity * totalCells);

    % Loop through each center
    for centerIndex = 1:size(centers, 1)
        xCenter = centers(centerIndex, 1);
        yCenter = centers(centerIndex, 2);

        % Create a grid of possible positions within the circle
        [xGrid, yGrid] = meshgrid(1:gridSize, 1:gridSize);

        % Calculate distances from the center to each position
        distances = sqrt((xGrid - xCenter).^2 + (yGrid - yCenter).^2);
        % Find available positions inside the circle and not already occupied
        for x = 1:gridSize
            for y = 1:gridSize
                if distances(x, y) <= radius && isempty(grid{x, y})
                    availablePositions = [availablePositions; x, y];
                end
            end
        end
    end

    % Shuffle the available positions
    shuffledPositions = availablePositions(randperm(size(availablePositions, 1)), :);

    % Calculate the number of positions to place based on desired density
    numPositionsToPlace = min(2 * numInitialFood, size(shuffledPositions, 1)); % Multiply by 2 for two centers

    % Place food in the available positions
    for i = 1:numPositionsToPlace
        x = shuffledPositions(i, 1);
        y = shuffledPositions(i, 2);
        grid{x, y} = 'F';
    end

    % Check if there are more food particles than required
    if numPositionsToPlace > 16000
        % Calculate the excess food particles
        excessFood = numPositionsToPlace - 16000;

        % Find the indices of food particles and shuffle them
        foodIndices = find(strcmp(grid, 'F'));
        shuffledFoodIndices = foodIndices(randperm(length(foodIndices)));

        % Remove the excess food particles up to the minimum of excessFood and the number of available indices
        for i = 1:min(excessFood, length(shuffledFoodIndices))
            [x, y] = ind2sub([gridSize, gridSize], shuffledFoodIndices(i));
            grid{x, y} = []; % Remove the food particle
        end
    end

    % Randomly place the initial populations of P (parasites)
    for i = 1:numInitialParasites
        x = randi(gridSize);
        y = randi(gridSize);
        while ~isempty(grid{x, y})
            x = randi(gridSize);
            y = randi(gridSize);
        end
        grid{x, y} = 'P';
        gridAges(x, y) = 0;  % New parasite's age starts at 0
    end

    % Define movement directions (N, S, E, W)
    directions = [-1, 0; 1, 0; 0, -1; 0, 1];

    % Define colors for F and P
    colorF = [0, 1, 0]; % Green color for F
    colorP = [1, 0, 0]; % Red color for P

    % Initialize arrays to track total food and parasite counts over time
    totalFoodCounts = zeros(1, numIterations + 1);
    totalParasiteCounts = zeros(1, numIterations + 1);

    % Number of iterations and delay for animation
    animationDelay = 0.2; % Adjust the delay between frames (in seconds)

    % Create a VideoWriter object (if requested)
    if createVideo
        if f1 == 3
            videoFileName = 'localised_food_agent_with_40pct_density_first_input_parameter.avi';
            videoObj = VideoWriter(videoFileName, 'Motion JPEG AVI');
            videoObj.FrameRate = 10; % Adjust the frame rate as needed
            open(videoObj);
        else
            videoFileName = 'localised_food_agent_with_40pct_density_second_input_parameter.avi';
            videoObj = VideoWriter(videoFileName, 'Motion JPEG AVI');
            videoObj.FrameRate = 10; % Adjust the frame rate as needed
            open(videoObj);
        end
    end

    % Create a figure for the animation (if requested)
    if createVideo
        figure;
    end

    for iteration = 1:numIterations
        % Update the total food and parasite counts for this iteration
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
                % Randomly choose one of the food center locations
                centerIndex = randi(size(centers, 1));
                xCenter = centers(centerIndex, 1);
                yCenter = centers(centerIndex, 2);

                % Generate random coordinates around the chosen center
                x = randi([xCenter - radius, xCenter + radius]);
                y = randi([yCenter - radius, yCenter + radius]);

                % Ensure that the coordinates are within the grid boundaries
                x = max(1, min(x, gridSize));
                y = max(1, min(y, gridSize));

                % Check if the cell is empty
                if isempty(grid{x, y})
                    grid{x, y} = 'F';
                end
            end
        end

        % Create the RGB image
        imageRGB = zeros(gridSize, gridSize, 3);
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
        scale_y = [0 200];
        imagesc(scale_x, scale_y, imageRGB);
        title('Annimation of agent-based model for first parameter regime')
        % Pause to create an animation effect
        pause(animationDelay);

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





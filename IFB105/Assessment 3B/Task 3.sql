USE treasurehunters;

# Insert
INSERT INTO badge (badgeName, badgeDescription)
VALUE ('Summer Rain', 'Beach, sun and holidays');

# Delete
DELETE FROM playerprogress
WHERE progress='complete';

# Update
UPDATE player
SET streetNumber=72, streetName='Evergreen Terrace', suburb='Springfield'
WHERE lastName='Halpin';
# CHECK ADDRESS TOO OR JUST LAST NAME

# Create Index
CREATE INDEX idx_story
ON quest (story);

# Create View
CREATE VIEW Inactive AS
    SELECT firstName, lastName, creationDateTime
    FROM player
    WHERE username IN (
            SELECT username
            FROM playerprogress
            WHERE playerprogress.progress = 'inactive'
        );

SELECT * FROM Inactive;
DROP VIEW Inactive;


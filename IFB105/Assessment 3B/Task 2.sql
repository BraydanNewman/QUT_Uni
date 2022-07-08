# ----------------------------
# TASK 2
# ----------------------------

USE treasurehunters;

# Query 1
SELECT treasureID, description, points, type
FROM treasure
WHERE description LIKE '%brick%'
   OR description LIKE '%map%';

# Query 2
SELECT type, COUNT(type) AS Count
FROM treasure
GROUP BY type
ORDER BY Count ASC;

# Query 3
SELECT badge.badgeName, badge.badgeID, MAX(p.cost)
FROM badge
         INNER JOIN purchase p on badge.badgeID = p.badgeID;

# Query 4
SELECT b.badgeName, p.firstName, p.lastName, p.email
FROM purchase
         INNER JOIN badge b on purchase.badgeID = b.badgeID
         INNER JOIN player p on purchase.username = p.username
ORDER BY b.badgeName, p.firstName, p.lastName;

# Query 5
SELECT p.firstName, p.lastName, p.username, COUNT(q.advanceQuestID) AS AdvanceQuestCount
FROM playerprogress
         INNER JOIN player p on playerprogress.username = p.username
         INNER JOIN quest q on playerprogress.questID = q.questID
WHERE advanceQuestID IS NOT NULL
GROUP BY p.username;

# Query 6
SELECT
    s.storeID,

    s.storeName,

    COUNT(DISTINCT p.username) AS 'PurchaseC',

    ((SELECT COUNT(player.username) FROM player) - COUNT(DISTINCT p.username)) AS 'NoPurchaseC',

    SUM(cost) AS 'MoneySpent',

    (SELECT p.badgeID HAVING MAX(p.cost)) AS 'MaxB',

    (SELECT p.badgeID HAVING MIN(p.cost)) AS 'MinB',

    AVG(cost) AS AvrageCost
FROM purchase AS p
RIGHT JOIN store s on s.storeID = p.storeID
GROUP BY s.storeID;

# ----------------------------
# TASK 3
# ----------------------------

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

# ----------------------------
# TASK 4
# ----------------------------

USE treasurehunters;

REVOKE INSERT, DELETE ON player FROM 'catie'@'localhost';

GRANT INSERT, DELETE ON quest TO 'manav'@'localhost';

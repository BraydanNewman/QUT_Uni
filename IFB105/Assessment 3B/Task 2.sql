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
    storeName,
    SUM(purchase.cost),
    purchase.badgeID,

FROM purchase
RIGHT JOIN store s on s.storeID = purchase.storeID
RIGHT JOIN player p on p.username = purchase.username
GROUP BY purchase.storeID;

SELECT *
FROM purchase
RIGHT OUTER JOIN player p on p.username = purchase.username






#SELECT Orders.OrderID, Customers.CustomerName, Orders.OrderDate
# FROM Orders
# INNER JOIN Customers ON Orders.CustomerID=Customers.CustomerID;
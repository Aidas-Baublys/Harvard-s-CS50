-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Get crime decription
SELECT description
FROM crime_scene_reports
WHERE year = 2021
AND month = 7
AND day = 28
AND street = "Humphrey Street";

-- Theft of the CS50 duck took place at 10:15am
-- at the Humphrey Street bakery. Interviews were conducted today
-- with three witnesses who were present at the time –
-- each of their interview transcripts mentions the bakery.
-- Littering took place at 16:36. No known witnesses.

-- Get interviews
SELECT transcript
FROM interviews
WHERE year = 2021
AND month = 7
AND day = 28;

-- Sometime within ten minutes of the theft, I saw the thief
-- get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot,
-- you might want to look for cars that left the parking lot in
-- that time frame.

-- I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at Emma's bakery,
-- I was walking by the ATM on Leggett Street and saw the
-- thief there withdrawing some money.

-- As the thief was leaving the bakery, they called someone
-- who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning
-- to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone
-- to purchase the flight ticket.

-- Get info from bakery around the time from the report and interview
SELECT activity, license_plate, hour, minute
FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day = 28
AND hour = 10
AND minute > 15
AND minute < 25;

-- Suspect plates:
+----------+---------------+------+--------+
| activity | license_plate | hour | minute |
+----------+---------------+------+--------+
| exit     | 5P2BI95       | 10   | 16     |
| exit     | 94KL13X       | 10   | 18     |
| exit     | 6P58WS2       | 10   | 18     |
| exit     | 4328GD8       | 10   | 19     |
| exit     | G412CB7       | 10   | 20     |
| exit     | L93JTIZ       | 10   | 21     |
| exit     | 322W7JE       | 10   | 23     |
| exit     | 0NTHK55       | 10   | 23     |
+----------+---------------+------+--------+

-- Get info from ATM
SELECT amount, account_number
FROM atm_transactions
WHERE year = 2021
AND month = 7
AND day = 28
AND atm_location = "Leggett Street"
AND transaction_type = "withdraw";

+--------+----------------+
| amount | account_number |
+--------+----------------+
| 48     | 28500762       |
| 20     | 28296815       |
| 60     | 76054385       |
| 50     | 49610011       |
| 80     | 16153065       |
| 20     | 25506511       |
| 30     | 81061156       |
| 35     | 26013199       |
+--------+----------------+

-- Get call info
SELECT caller, receiver
FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60;

+----------------+----------------+
|     caller     |    receiver    |
+----------------+----------------+
| (130) 555-0289 | (996) 555-8899 |
| (499) 555-9472 | (892) 555-8872 |
| (367) 555-5533 | (375) 555-8161 |
| (499) 555-9472 | (717) 555-1342 |
| (286) 555-6063 | (676) 555-6554 |
| (770) 555-1861 | (725) 555-3243 |
| (031) 555-6622 | (910) 555-3251 |
| (826) 555-1652 | (066) 555-9701 |
| (338) 555-6650 | (704) 555-2131 |
+----------------+----------------+

-- Get earliest flight info
SELECT id, hour, minute
FROM flights
WHERE year = 2021
AND month = 7
AND day = 29
AND origin_airport_id IN
(
  SELECT id FROM airports
  WHERE city = "Fiftyville"
)
ORDER BY hour
LIMIT 1;

+----+------+--------+
| id | hour | minute |
+----+------+--------+
| 36 | 8    | 20     |
+----+------+--------+

-- Get destination
SELECT city
FROM airports
WHERE id =
(
  SELECT destination_airport_id
  FROM flights
  WHERE id = 36
);

+---------------+
|     city      |
+---------------+
| New York City |
+---------------+

-- Get passport numbers from flight
SELECT passport_number
FROM passengers
WHERE flight_id = 36;

+-----------------+
| passport_number |
+-----------------+
| 7214083635      |
| 1695452385      |
| 5773159633      |
| 1540955065      |
| 8294398571      |
| 1988161715      |
| 9878712108      |
| 8496433585      |
+-----------------+

-- Combine everything and find thief
SELECT name
FROM people
WHERE phone_number IN
(
  SELECT caller
  FROM phone_calls
  WHERE year = 2021
  AND month = 7
  AND day = 28
  AND duration < 60
)
AND passport_number IN
(
  SELECT passport_number
  FROM passengers
  WHERE flight_id =
  (
    SELECT id
    FROM flights
    WHERE year = 2021
    AND month = 7
    AND day = 29
    AND origin_airport_id IN
    (
      SELECT id FROM airports
      WHERE city = "Fiftyville"
    )
    ORDER BY hour
    LIMIT 1
  )
)
AND license_plate IN
(
  SELECT license_plate
  FROM bakery_security_logs
  WHERE year = 2021
  AND month = 7
  AND day = 28
  AND hour = 10
  AND minute > 15
  AND minute < 25
)
AND id IN
(
  SELECT person_id
  FROM bank_accounts
  WHERE account_number IN
  (
    SELECT account_number
    FROM atm_transactions
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND atm_location = "Leggett Street"
    AND transaction_type = "withdraw"
  )
);

+-------+
| name  |
+-------+
| Bruce |
+-------+

-- Find accomplice
SELECT name
FROM people
WHERE phone_number IN
(
  SELECT receiver
  FROM phone_calls
  WHERE year = 2021
  AND month = 7
  AND day = 28
  AND duration < 60
  AND caller =
  (
    SELECT phone_number
    FROM people
    WHERE name = "Bruce"
  )
);

+-------+
| name  |
+-------+
| Robin |
+-------+
-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Step 1: Check the database schema for available tables and columns
.schema crime_scene_reports

-- Step 2: Find the crime description for the theft on JULY 28, 2024 at Humphrey Street
-- This tells us What happened, where, and may provide initial clues or references to witnesses
SELECT description
FROM crime_scene_reports
WHERE year = 2024
    AND month = 7
    AND day = 28
    AND street = "Humphrey Street";

-- Step 3: Read interviews taken on the same day that mention "bakery" - the location of theft.
-- This identifies potential eyewitnesses and gives us clues such as car, ATM, flight and call details.
SELECT name, transcript
FROM interviews
WHERE year = 2024
    AND month = 7
    AND day = 28
    AND transcript LIKE "%bakery%";


-- Step 4: Identify people who exited the bakery parking lot shortly after the crime (10:15–10:25 AM).
-- These are our initial suspects based on the timing of the theft and Ruth’s eyewitness report.
SELECT p.name, b.license_plate, b.hour, b.minute
FROM bakery_security_logs b
JOIN people p ON b.license_plate = p.license_plate
WHERE year = 2024
    AND month = 7 AND day = 28 AND hour = 10
    AND minute BETWEEN 15 AND 25
    AND activity = "exit"
ORDER BY minute;

-- Step 5: From our list of suspects, find out who withdrew money from the Leggett Street ATM that morning.
-- This matches Eugene’s statement that the thief withdrew cash at that ATM before the crime.
SELECT p.name, a.amount, a.transaction_type, a.atm_location
FROM people p
JOIN bank_accounts ba ON p.id = ba.person_id
JOIN atm_transactions a ON ba.account_number = a.account_number
WHERE
    a.year = 2024 AND a.month = 7 AND a.day = 28
    AND a.atm_location = "Leggett Street"
    AND a.transaction_type = "withdraw"
    AND p.name IN ("Vanessa", 'Bruce', "Barry", "Luca", "Sofia", "Iman", "Diana", "Kelsey")
ORDER BY p.name;

-- Step 6: From the narrowed suspects, check who made a short phone call (< 60 seconds) on the day of the theft.
-- According to Raymond, the thief made a call while leaving the bakery and asked someone to book a flight.
SELECT p.name, pc.duration, pc.caller, pc.receiver
FROM people p
JOIN phone_calls pc ON p.phone_number = pc.caller
WHERE pc.year = 2024
    AND pc.month = 7
    AND pc.day = 28
    AND pc.duration < 60
    AND p.name IN ("Bruce","Diana","Iman","Luca")
ORDER BY pc.duration;

-- Step 7: Get the ID of Fiftyville’s airport to find flights departing from it.
-- Needed to locate the earliest flight out of Fiftyville on July 29.
SELECT id , abbreviation, full_name
FROM airports
WHERE city = "Fiftyville";

-- Step 8: Find the earliest flight leaving Fiftyville on July 29, 2024.
-- The thief mentioned they would take the earliest flight out.
SELECT id, hour, minute, destination_airport_id
FROM flights
WHERE origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville")
    AND year = 2024
    AND month = 7
    AND day = 29
ORDER BY hour, minute
LIMIT 1;

-- Step 9: Identify passengers on that first flight (Flight ID = 36).
-- This shows who boarded the flight; helps us pinpoint the suspect who left town.
SELECT p.name
FROM passengers ps
JOIN people p ON ps.passport_number = p.passport_number
WHERE ps.flight_id = 36;


-- Step 10: Find the city the thief escaped to by checking the destination of that flight.
-- Needed for the final answer — where the thief went.
SELECT city
FROM airports
WHERE id = 4;

-- Step 11: Identify the person who received the short phone call from Bruce (the thief).
-- This tells us who the accomplice is — the person who booked the flight for Bruce.
SELECT name
FROM people
WHERE phone_number = "(375) 555-8161"

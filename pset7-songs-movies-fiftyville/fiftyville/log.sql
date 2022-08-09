-- Keep a log of any SQL queries you execute as you solve the mystery

-- Starting information: The theft took place on July 28, 2021 and that it took place on Humphrey Street.
-- Get further description about the CS50 duck theft 
-- id|year|month|day|street|description
-- 295|2021|7|28|Humphrey Street|Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. 
-- Interviews were conducted today with three witnesses who were present at the time 
-- each of their interview transcripts mentions the bakery.
SELECT * FROM crime_scene_reports
WHERE year = 2021 
    AND month = 7 
    AND day = 28 
    AND street = "Humphrey Street";


-- Look at the 3 detailed interview transcripts mentioned in the crime scene report 
-- id|name|year|month|day|transcript
-- 161|Ruth|2021|7|28|Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- 162|Eugene|2021|7|28|I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- 163|Raymond|2021|7|28|As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
SELECT * FROM interviews
WHERE year = 2021 
    AND month = 7   
    AND day = 28;


-- Following up on Ruth -> Thief got in a car within 10min of crime in bakery parking lot
--id|year|month|day|hour|minute|activity|license_plate
-- 260|2021|7|28|10|16|exit|5P2BI95
-- 261|2021|7|28|10|18|exit|94KL13X
-- 262|2021|7|28|10|18|exit|6P58WS2
-- 263|2021|7|28|10|19|exit|4328GD8
-- 264|2021|7|28|10|20|exit|G412CB7
-- 265|2021|7|28|10|21|exit|L93JTIZ
-- 266|2021|7|28|10|23|exit|322W7JE
-- 267|2021|7|28|10|23|exit|0NTHK55
SELECT * FROM bakery_security_logs
WHERE year = 2021 
    AND month = 7 
    AND day = 28  
    AND hour = 10 
    AND minute BETWEEN 15 AND 25;


-- Check the  names of all people who's license plates were in the bakery parking lot at 10:15 - 10:25
-- id|name|phone_number|passport_number|license_plate
-- 221103|Vanessa|(725) 555-4692|2963008352|5P2BI95
-- 243696|Barry|(301) 555-4174|7526138472|6P58WS2
-- 396669|Iman|(829) 555-5269|7049073643|L93JTIZ
-- 398010|Sofia|(130) 555-0289|1695452385|G412CB7
-- 467400|Luca|(389) 555-5198|8496433585|4328GD8
-- 514354|Diana|(770) 555-1861|3592750733|322W7JE
-- 560886|Kelsey|(499) 555-9472|8294398571|0NTHK55
-- 686048|Bruce|(367) 555-5533|5773159633|94KL13X
SELECT * FROM people 
WHERE license_plate 
    IN (SELECT license_plate FROM bakery_security_logs 
        WHERE year = 2021 
            AND month = 7   
            AND day = 28 
            AND hour = 10 
            AND minute BETWEEN 15 AND 25);


-- Get the bank account id's of people who were in the bakery parking lot between 10:15 - 10:25
-- id|name|phone_number|passport_number|license_plate|account_number|person_id|creation_year
-- 686048|Bruce|(367) 555-5533|5773159633|94KL13X|49610011|686048|2010
-- 514354|Diana|(770) 555-1861|3592750733|322W7JE|26013199|514354|2012
-- 396669|Iman|(829) 555-5269|7049073643|L93JTIZ|25506511|396669|2014
-- 467400|Luca|(389) 555-5198|8496433585|4328GD8|28500762|467400|2014
-- 243696|Barry|(301) 555-4174|7526138472|6P58WS2|56171033|243696|2018
SELECT * FROM people 
JOIN bank_accounts 
    ON bank_accounts.person_id = people.id 
WHERE license_plate 
    IN (SELECT license_plate FROM bakery_security_logs 
        WHERE year = 2021 
            AND month = 7 
            AND day = 28 
            AND hour = 10 
            AND minute BETWEEN 15 AND 25);


-- Following up on Eugene where he saw the thief withdraw $ from ATM on Leggett Street 
-- -- Using the bank account ids from previous query
-- id|name|phone_number|passport_number|license_plate|account_number|person_id|creation_year|id|account_number|year|month|day|atm_location|transaction_type|amount
-- 686048|Bruce|(367) 555-5533|5773159633|94KL13X|49610011|686048|2010|267|49610011|2021|7|28|Leggett Street|withdraw|50
-- 514354|Diana|(770) 555-1861|3592750733|322W7JE|26013199|514354|2012|336|26013199|2021|7|28|Leggett Street|withdraw|35
-- 396669|Iman|(829) 555-5269|7049073643|L93JTIZ|25506511|396669|2014|288|25506511|2021|7|28|Leggett Street|withdraw|20
-- 467400|Luca|(389) 555-5198|8496433585|4328GD8|28500762|467400|2014|246|28500762|2021|7|28|Leggett Street|withdraw|48
SELECT * FROM people
    JOIN bank_accounts 
        ON bank_accounts.person_id = people.id
    JOIN atm_transactions   
        ON atm_transactions.account_number = bank_accounts.account_number
    WHERE atm_location = "Leggett Street"   
        AND year = 2021 
        AND month = 7 
        AND day = 28
        AND license_plate 
            IN (SELECT license_plate FROM bakery_security_logs
                WHERE year = 2021 
                    AND month = 7 
                    AND day = 28 
                    AND hour = 10 
                    AND minute BETWEEN 15 AND 25);


-- Check our current suspects: Luca, Burce, Diana, Iman to see if any <1min calls were made after crime
-- Follow up based on witness report of call 
-- New Suspect is either Bruce or Diana
-- id|caller|receiver|year|month|day|duration
-- 233|(367) 555-5533|(375) 555-8161|2021|7|28|45
-- 236|(367) 555-5533|(344) 555-9601|2021|7|28|120
-- 245|(367) 555-5533|(022) 555-4052|2021|7|28|241
-- 255|(770) 555-1861|(725) 555-3243|2021|7|28|49
-- 285|(367) 555-5533|(704) 555-5790|2021|7|28|75
SELECT * FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28
AND phone_calls.caller IN (SELECT people.phone_number FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_location = "Leggett Street"   
AND year = 2021 AND month = 7 AND day = 28
AND license_plate IN (SELECT license_plate FROM bakery_security_logs
WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25));


-- Check earliest airport flights out July 29, 2021 that have a passenger named Bruce or Diana 
-- Thief was BRUCE
SELECT * FROM passengers 
JOIN flights ON flights.id = passengers.flight_id 
WHERE passengers.passport_number = 5773159633 OR passengers.passport_number = 3592750733
ORDER BY flights.minute DESC LIMIT 1;


-- Find the city to which Bruce escaped to... 
SELECT * FROM airports 
WHERE airports.id IN (SELECT flights.destination_airport_id FROM passengers 
JOIN flights ON flights.id = passengers.flight_id 
WHERE passengers.passport_number = 5773159633 OR passengers.passport_number = 3592750733
ORDER BY flights.minute DESC LIMIT 1);


JOIN flights ON flights.id = passengers.flight_id 
WHERE passengers.passport_number = 5773159633 OR passengers.passport_number = 3592750733
ORDER BY flights.minute DESC LIMIT 1;


-- Find the name of Bruce's accomplishmen by checking outgoing calls made close to crime time 
-- id|caller|receiver|year|month|day|duration
-- 233|(367) 555-5533|(375) 555-8161|2021|7|28|45
-- 236|(367) 555-5533|(344) 555-9601|2021|7|28|120
-- 245|(367) 555-5533|(022) 555-4052|2021|7|28|241
-- 285|(367) 555-5533|(704) 555-5790|2021|7|28|75
SELECT * FROM phone_calls 
WHERE caller = "(367) 555-5533" 
AND year = 2021 AND month = 7 AND day = 28;


-- Check from phone numbers to see if they were on the first flight out on July 29, 2021 
-- to find BRUCE's accomplice 
SELECT people.name FROM people
WHERE people.phone_number IN 
    (SELECT receiver FROM phone_calls WHERE caller = "(367) 555-5533" AND year = 2021 AND month = 7 AND day = 28)
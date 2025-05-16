-- Keep a log of any SQL queries you execute as you solve the mystery.

-- PASSO 1: Obter o relatório da cena do crime.
-- Procurar por crimes que ocorreram em 28 de Julho de 2024 na Humphrey Street.
-- O objetivo é encontrar a descrição do crime e, principalmente, se há menção a testemunhas ou entrevistas.
SELECT description
FROM crime_scene_reports
WHERE year = 2024 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

-- PASSO 2: Encontrar as entrevistas das testemunhas.
-- O relatório da cena do crime mencionou três testemunhas entrevistadas no dia 28/07/2024,
-- e que todas as transcrições mencionam a "bakery".
SELECT name, transcript
FROM interviews
WHERE year = 2024 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';

-- PASSO 3: Investigar a pista da testemunha Ruth - Carros saindo da padaria.
-- O roubo foi às 10:15. Ruth viu o ladrão sair no estacionamento da padaria entre 10:15 e 10:25 do dia 28/07/2024.
-- Procurar por placas de carro (license_plate) nos registros de segurança da padaria (bakery_security_logs).
SELECT license_plate
FROM bakery_security_logs
WHERE year = 2024 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = 'exit';

-- PASSO 4: Investigar a pista da testemunha Eugene - Saque no ATM.
-- Eugene viu o ladrão sacando dinheiro em um ATM na Leggett Street na manhã do dia 28/07/2024.
-- Procurar por números de conta (account_number) associados a transações de saque (withdraw) nesse local e data.
SELECT account_number
FROM atm_transactions
WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

-- PASSO 5: Investigar a pista da testemunha Raymond - Ligação telefônica.
-- Raymond ouviu o ladrão fazer uma ligação de menos de um minuto ao sair da padaria no dia 28/07/2024.
-- Procurar por números de telefone de quem fez a chamada (caller).
SELECT caller
FROM phone_calls
WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60;

-- PASSO 6: Investigar a pista da testemunha Raymond - O Voo.
-- O ladrão planejava pegar o primeiro voo de Fiftyville no dia 29/07/2024.

-- PASSO 6a: Encontrar o ID do aeroporto de Fiftyville.
SELECT id
FROM airports
WHERE city = 'Fiftyville';

-- PASSO 6b: Encontrar o ID do primeiro voo e o ID do aeroporto de destino,
-- partindo do aeroporto de Fiftyville (ID 8) no dia 29/07/2024.
-- Ordenar por hora e minuto para garantir que é o primeiro voo.
SELECT id, destination_airport_id
FROM flights
WHERE origin_airport_id = 8 AND year = 2024 AND month = 7 AND day = 29
ORDER BY hour, minute
LIMIT 1;

-- PASSO 6c: Listar os números de passaporte dos passageiros do voo com ID 36.
SELECT passport_number
FROM passengers
WHERE flight_id = 36;

-- PASSO 7: Cruzar todas as informações para identificar o LADRÃO.
-- O ladrão deve:
--   1. Ter uma das placas de carro que saíram da padaria (lista do PASSO 3).
--   2. Ter uma das contas bancárias que fizeram saque no ATM (lista do PASSO 4), o que nos dá um person_id.
--   3. Ter um dos números de telefone que fizeram a ligação curta (lista do PASSO 5).
--   4. Ter um dos números de passaporte do voo de fuga (lista do PASSO 6c).
SELECT p.name
FROM people p
JOIN bank_accounts ba ON p.id = ba.person_id
WHERE p.license_plate IN ('5P2BI95', '94KL13X', '6P58WS2', '4328GD8', 'G412CB7', 'L93JTIZ', '322W7JE', '0NTHK55')
  AND ba.account_number IN ('28500762', '28296815', '76054385', '49610011', '16153065', '25506511', '81061156', '26013199')
  AND p.phone_number IN ('(130) 555-0289', '(499) 555-9472', '(367) 555-5533', '(286) 555-6063', '(770) 555-1861', '(031) 555-6622', '(826) 555-1652', '(338) 555-6650')
  AND p.passport_number IN ('7214083635', '1695452385', '5773159633', '1540955065', '8294398571', '1988161715', '9878712108', '8496433585');

-- PASSO 8: Descobrir a cidade para onde o ladrão (Bruce) escapou.
-- Sabemos que o ID do aeroporto de destino do voo de Bruce (ID 36) era 4 (do PASSO 6b).
SELECT city
FROM airports
WHERE id = 4;

-- PASSO 9a: Encontrar o número de telefone de Bruce.
SELECT phone_number
FROM people
WHERE name = 'Bruce';

-- PASSO 9b: Encontrar o nome da pessoa que recebeu a ligação de Bruce.
-- Usar o número de telefone de Bruce ('(367) 555-5533') como 'caller'
-- e procurar o 'receiver' da ligação curta no dia 28/07/2024.
SELECT p.name
FROM people p
JOIN phone_calls pc ON p.phone_number = pc.receiver
WHERE pc.caller = '(367) 555-5533' AND pc.year = 2024 AND pc.month = 7 AND pc.day = 28 AND pc.duration < 60;

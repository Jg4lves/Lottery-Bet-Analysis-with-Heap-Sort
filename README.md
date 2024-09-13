### Explanation of Input Data

3000 -> <Total Bet Amount>
5 -> <Number of Bets>
1 2 3 5 8 13 25 33 42 48 -> <Drawn Numbers>
1234567890ABCDEF1234567890ABCDEF 1 2 3 9 11 17 19 20 21 30 34 38 39 40 44 -> <bet code> <bet numbers>
1223334444555556666667777777ABCD 2 3 5 9 13 14 15 17 18 20 33 35 40 41 42 -> <bet code> <bet numbers>
AAAAAABBBBBCCCCCDDDDDEEEEEFFFFFF 1 2 5 8 9 11 15 16 19 21 27 33 35 42 49 -> <bet code> <bet numbers>
0A1B2C3D4E5F6A7B8C9DAEBFCEDFE0F1 3 4 5 7 11 16 18 20 24 25 31 34 35 42 50 -> <bet code> <bet numbers>
F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0 3 4 7 9 15 18 23 24 26 31 32 38 41 43 48 -> <bet code> <bet numbers>

### Explanation of OutPut Data

[2:6:750] -> <bets that had the maximum count of matches> <count of matches for these bets> <prize amount allocated to each bet>
1223334444555556666667777777ABCD -> <bet code>
AAAAAABBBBBCCCCCDDDDDEEEEEFFFFFF -> <bet code>
[1:2:1500] -> <bets that had the minimum count of matches> <count of matches for these bets> <prize amount allocated to each bet>
F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0 -> <bet code>

/*
1. Каква е сложността на следната функция и защо?
2. Откриите бъга.
*/
int fibs(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fibs(n - 1) + fibs(n - 2);
    }
}

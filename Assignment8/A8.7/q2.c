int q2(int x, int y, int z) {
    int i = 0;
    if (x < 10 || x > 18) {
        return 0;
    } else {
        i = x - 10;
        switch(i) {
            case 0: 
                i = y + z;
                break;
            case 2: 
                i = y-z;
                break;
            case 4: 
                if (y > z) {
                    i = 1;
                } else {
                    i = 0;
                }
                break;
            case 6:
                if (z > y) {
                    i = 1;
                } else {
                    i = 0;
                }
                break;
            case 8:
                if (y == z) {
                    i = 1;
                } else {
                    i = 0;
                }
                break;
            default: 
                i = 0;
        }
    }
    return i;
}

int main() {
    int arr[4] = {0,0,0,0};
    arr[3] = q2(arr[0], arr[1], arr[2]);

    for (int i = 0; i<4; i++) {
        printf("%d\n", arr[i]);
    }
    return 0;
}
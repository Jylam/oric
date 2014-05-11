int main(int argc, char *argv[]) {
    int i;
    char *text = (char*)0xbb80;
    for(i=0; i<10; i++) {
        text[i] = 65;
    }
}

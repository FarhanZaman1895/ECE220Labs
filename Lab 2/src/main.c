/* INCLUDES */
#include<stdio.h>
#include <locale.h>

#define ERR -1

#define FROM_SIZE 3
#define TO_SIZE 4

int main() {
    /* SETUP */
    FILE* key_file;
    FILE* raw_file;
    FILE* encoded_file;
    setlocale(LC_ALL, "en_US.UTF-8");

    char key_path[] = "/home/fzaman/Coding/C/ECE220/Labs/Lab 2/data/Key.dat";
    char raw_path[] = "/home/fzaman/Coding/C/ECE220/Labs/Lab 2/data/Raw.dat";
    char encoded_path[] = "/home/fzaman/Coding/C/ECE220/Labs/Lab 2/data/Encoded.dat";

    //buf_in : array of size 3 used as an input buffer for the base 64 conversion
    unsigned char buf_in[FROM_SIZE];
    //buf_out : array of size 4 used as an output buffer for the base 64 conversion
    unsigned char buf_out[TO_SIZE];

    // keys: array to store the index table
    char keys[64];

    int count;
    int total_char;

    /* FILES */
    key_file = fopen(key_path,"r");

    // Check if the file can be read
    if (key_file == NULL) {
        printf("The file could not be found\n");
        return ERR;
    }

    // Load data from file to an array
    for(int i = 0;i < 64; i++) {
        int ch = fgetc(key_file);
        if (ch == EOF) {
            printf("Error reading file\n");
            fclose(key_file);
            return ERR;
        }

        keys[i] = (char)ch;
    }
    fclose(key_file);

    // Open and check if raw file exists
    raw_file = fopen(raw_path, "r");

    if (raw_file == NULL) {
        printf("The file could not be found\n");
        return ERR;
    }

    // Open and check if encoded file exists
    encoded_file = fopen(encoded_path,"w");

    //check if  decoded file cannot be found
    if (encoded_file == NULL) {
        printf("The file could not be found\n");
        return ERR;
    }

    /* ENCODING */
    // NOTE: This is mostly left untouched from the template save the sections
    // where we are told to edit code in and some formatting for readability
    total_char=0;

    // fread here read each time 3 bytes or chars  from the input raw file(fin) and store it in buf_in
    //count= The total number of elements successfully read
    // while loop stops when count is not equal to 3

    while ((count = fread(buf_in, 1, FROM_SIZE, raw_file)) == FROM_SIZE) {

        // select the last six bits from buf_in[0] using the mask 0xFC=1111 1100 ,
        // then shift the bit two position to the right >>2 to rearrange the six bits and
        // if buf_in[0]=[b_7|b_6|b_5|b_4|b_3|b_2|b_1|b_0]then  buf_out[0]= [0|0|b_7|b_6|b_5|b_4|b_3|b_2]
        buf_out[0] = keys[(buf_in[0] & (0xFC)) >> 2];


        // select the first two bits from buf_in[0] using the mask 0x03=0000 0011 ,
        // then shift the bit four position to the left <<4 to rearrange the two bits and
        // select the last four bits from buf_in[1] using the mask 0xF0=1111 0000 ,
        // then shift the bit four position to the right >>4 to rearrange the four bits
        // if buf_in[0]=[b_7|b_6|b_5|b_4|b_3|b_2|b_1|b_0]
        // and buf_in[1]=[c_7|c_6|c_5|c_4|c_3|c_2|c_1|c_0]
        // then  buf_out[1]= [0|0|b_1|b_0|c_7|c_6|c_5|c_4]
        // | (or in binary) is used to concatenate the bytes after the bits are selected and rearranged
        buf_out[1] = keys[((buf_in[0] & (0x03)) << 4) | ((buf_in[1] & (0xF0)) >> 4)];


        // 0x0F=0000 1111  and  0xC0= 1100 0000
        buf_out[2] = keys[((buf_in[1] & (0x0F)) << 2) | ((buf_in[2] & (0xC0)) >> 6)];

        // 0x3F 00111111
        buf_out[3] = keys[(buf_in[2] & (0x3F))];

        // fwrite here writes all 4 characters of buf_out into fout
        fwrite(buf_out, TO_SIZE, 1, encoded_file);



        // file formatting
        total_char += TO_SIZE;
        if (total_char % 48 == 0) {
            // add return to line after 6 groups (line should contain 6 groups)
            fputc('\n', encoded_file);
        } else if (total_char %8 ==0) {
            // add a space for each separated into groups of 8 characters with a space between
            fputc(' ', encoded_file);
        }
    }

    if(count!=0) {
        buf_out[0] = keys[(buf_in[0] & (0xFC)) >> 2];
        if (count == 1) {
            buf_out[1] = keys[((buf_in[0] & (0x03)) << 4) | ((buf_in[1] & (0xF0)) >> 4)];
            buf_out[2] = '=';
        } else if (count == 2) {
            buf_out[1] = keys[((buf_in[0] & (0x03)) << 4) | ((buf_in[1] & (0xF0)) >> 4)];
            buf_out[2] = keys[((buf_in[1] & (0x0F)) << 2)];
        }
        buf_out[3] = '=';
        fwrite(buf_out, TO_SIZE, 1, encoded_file);
    }
    fclose(raw_file);
    fclose(encoded_file);

    return 0;
}

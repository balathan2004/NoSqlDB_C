// #include <stdio.h>
// #include <string.h>

// void splitString(char *input, char array[10][100]) {

//   char buffer[1024];

//   int buffIndex = 0;
//   int isBackTicks = 0;
//   int arrayCount = 0;

//   int backtickCount = 0;
//   for (int i = 0; input[i] != '\0'; i++) {
//     if (input[i] == '`')
//       backtickCount++;
//   }

//     for (int i = 0; input[i] != '\0'; i++) {

//       if(input[i]=='\n' ){
//       printf("found n",input[i]);

//       }
//        if(input[i]=='\0'){
//       printf("found null char",input[i]);

//       }
      
//     }

//   if (backtickCount % 2 != 0) {
//     printf("Error: unmatched backticks in input.\n");
//     return -1;
//   }

//   for (int i = 0; i < strlen(input); i++) {

//     char c = input[i];

//     if (c == '`') {
//       isBackTicks = !isBackTicks;

//       continue;
//     }

//     if (!isBackTicks && (c == ' ' || c == '\0' || c=='\n')) {
//       buffer[buffIndex] = '\0';
//       if (buffIndex > 0) {
//         strcpy(array[arrayCount++], buffer);
//         printf("[%s]", buffer);
//         buffIndex = 0;
//       }
//     } else if(c!='\0') {
//       buffer[buffIndex++] = c;
//     }

//     if (input[i] == '`')
//       printf("char found at index %d", i);
//   }

//   return array;
// }

// int main() {

//   char input[100];

//   printf("Type: ");

//   fgets(input, sizeof(input), stdin);

//   printf("\n input is = %s", input);

//   char array[10][100];

//   splitString(input, array);

//   return 0;
// }

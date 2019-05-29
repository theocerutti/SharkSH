/*
** EPITECH PROJECT, 2018
** my_strcmp.c
** File description:
** strcmp cd
*/

int my_strcmp_cd(char const *s1, char const *s2)
{
    int i;
    int len1;
    int len2;

    for (len1 = 0; s1[len1] != '\0'; len1++);
    for (len2 = 0; s2[len2] != '\0'; len2++);
    if (len1 != len2)
        return (0);
    for (i = 0; s1[i] != '\0'; i++) {
        if (s1[i] != s2[i])
            return (0);
    }
    return (1);
}
/*
#  AUTHOR:     Srizan Gangol
#  COURSE:      CSCE 4110
#  ASSIGNMENT:  Assignment #2
#  DESCRIPTION: Greedy algorithm: Change Calculator
#
#  Usuage:
#  $ g++ greedy.c -o greedy
#  $ ./greedy
#  >Enter the change: __
#  >Your Input was: __
#  YOUR CHANGE:
#  ..
#  .
*/

#include<bits/stdc++.h>

int main()
{
  float change;
  int dollar, quater, nikel, dime, penny;

  printf (">Enter the change: ");
  scanf ("%f",&change);

  printf (">Your Input was: %.2f \n\n",change);

  dollar = change/1;
  change = (change - dollar)*100;
  // printf ("TEST $: %.2f \n",change);

  quater = change/25;
  change = change - (quater*25);
  // printf ("TEST .25: %.2f \n",change);

  dime = change/10;
  change = change - (dime*10);
  // printf ("TEST .10: %.2f \n",change);

  nikel = change /5;
  change = change - (nikel*5);
  // printf ("TEST .5: %.2f \n",change);

  penny = change;
  // printf ("TEST .1: %.2f \n",change);

  printf(" YOUR CHANGE:\n -----------\n Dollars ($):\t%d \n Quarter (.25):\t%d \n Dime (.10):\t%d \n Nikel(.05):\t%d \n Penny(.01):\t%.0f\n ", dollar, quater, dime, nikel, change );

return 0;
}

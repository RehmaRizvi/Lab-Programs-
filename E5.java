/*COC3930: Algorithms and Operating Systems Lab
EXPERIMENT-5
Name : Abiha Fatima
S.No. : 57
Faculty No. : 19COB277
Enrollment No. : GL2987
*/
import java.util.Scanner;
class PatternMatching
{
    //Implementation of Knuth-Morris-Pratt (KMP) String matching algorithm
    public static void KMP_Algorithm(String A, String B)
    {
        int count = 0;
        char[] BcharArray = B.toCharArray();
        if (A == null || B.length() > A.length())
        {
            System.out.println("The pattern does not occur as main string is empty/shorter than pattern string");
            return;
        }
        int[] storeNextArr = new int[B.length() + 1];  //storeNextArr stores the index of the next best match
        if (B == null || B.length() == 0)
        {
            System.out.println("The pattern does not occur as Pattern string is empty");
            return;
        }
        for (int i = 1; i < B.length(); i++)
        {
            int j = storeNextArr[i + 1];

            while (j > 0 && BcharArray[j] != BcharArray[i]) {
                j = storeNextArr[j];
            }

            if (j > 0 || BcharArray[j] == BcharArray[i]) {
                storeNextArr[i + 1] = j + 1;
            }
        }

        for (int i = 0, j = 0; i < A.length(); i++)
        {
            if (j < B.length() && A.charAt(i) == B.charAt(j))
            {
                if (++j == B.length())
                {
                    System.out.println("The pattern occurs at indices: " +
                            "("+(i - j + 1)+ ", " + i + ")");
                    count++;
                }
            }
            else if (j > 0)
            {
                j = storeNextArr[j];
                i--;	// since `i` will be incremented in the next iteration
            }
        }
        System.out.println("Total number of occurences of pattern in main string is: "+count);
    }

    // main method to implement the KMP algorithm
    public static void main(String[] args)
    {
        PatternMatching obj = new PatternMatching();
        Scanner sc = new Scanner(System.in);
        System.out.printf("Enter the main String:\t");
        String text = sc.nextLine();
        System.out.printf("Enter the pattern:\t");
        String pattern = sc.nextLine();
        long start = System.currentTimeMillis();
        obj.KMP_Algorithm(text, pattern);
        long end = System.currentTimeMillis();
        System.out.println("\nTotal Time taken for the execution of the function in milli seconds: "+ (end-start));
    }
}
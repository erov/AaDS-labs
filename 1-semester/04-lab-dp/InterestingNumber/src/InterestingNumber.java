import java.math.BigInteger;
import java.nio.channels.Pipe;
import java.util.Arrays;
import java.util.Queue;
import java.util.Scanner;

public class InterestingNumber {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();

        BigInteger[][] dp = new BigInteger[10][];
        BigInteger base = BigInteger.valueOf(-1);
        for (int i = 0; i <= 9; i++) {
            dp[i] = new BigInteger[n + 1];
            for (int j = 0; j <= n; j++) {
                dp[i][j] = base;
            }
        }

        dp[0][0] = BigInteger.ZERO;
        int head, tail;
        int[] q = new int[1_000_047];

        for (int sum = 0; sum <= n; sum++) {
            if (sum != 0) {
                head = 0;
                tail = 0;
                for (int ost = 0; ost <= n; ost++) {
                    if (!dp[0][ost].equals(base)) {
                        q[tail++] = ost;
                    }
                }
                while (head < tail) {
                    int ost = q[head++];
                    int newOst = ost * 10 % n;
                    BigInteger cur = dp[0][ost].multiply(BigInteger.TEN);
                    if (dp[0][newOst].equals(base)) {
                        q[tail++] = newOst;
                    }
                    if (dp[0][newOst].equals(base) || dp[0][newOst].compareTo(cur) > 0) {
                        dp[0][newOst] = cur;
                    }
                }
            }

            for (int ost = 0; ost <= n; ost++) {
                if (!dp[0][ost].equals(base)) {
                    for (int i = 1; i <= 9 && sum + i <= n; i++) {
                        int newOst = (ost * 10 + i) % n;
                        BigInteger cur = dp[0][ost].multiply(BigInteger.TEN).add(BigInteger.valueOf(i));
                        if (dp[i][newOst].equals(base) || dp[i][newOst].compareTo(cur) > 0) {
                            dp[i][newOst] = cur;
                        }
                    }
                }
            }

//            for (int i = 0; i < 10; i++) {
//                for (int j = 0; j <= n; j++) {
//                    System.out.print(dp[i][j] + " ");
//                }
//                System.out.println();
//            }
//            System.out.println();

            if (sum != n) {
                for (int i = 0; i < 9; i++) {
                    dp[i] = Arrays.copyOf(dp[i + 1], n + 1);
                }
                for (int i = 0; i <= n; i++) {
                    dp[9][i] = base;
                }
            }

//            for (int i = 0; i < 10; i++) {
//                for (int j = 0; j <= n; j++) {
//                    System.out.print(dp[i][j] + " ");
//                }
//                System.out.println();
//            }
//            System.out.println();
        }

        System.out.println(dp[0][0]);
    }
}

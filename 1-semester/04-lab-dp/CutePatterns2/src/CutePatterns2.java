import java.math.BigInteger;
import java.util.List;
import java.util.Scanner;

public class CutePatterns2 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n, m;
        final int mod = (1 << 30) + 1;

        n = input.nextInt();
        m = input.nextInt();

        if (n < m) {
            int tmp = m;
            m = n;
            n = tmp;
        }

        int sz = 1 << m;
        long[][] dp = new long[sz][];
        for (int i = 0; i < sz; i++) {
            dp[i] = new long[sz];
            for (int j = 0; j < sz; j++) {
                dp[i][j] = 1;
//                System.out.println(i + " " + j);
                for (int k = 1; k < m; k++) {
                    List<Integer> tmp = List.of((i & (1 << k)), (j & (1 << k)), (j & (1 << (k - 1))), (i & (1 << (k - 1))));
                    int zero = 0;
                    for (var it : tmp) {
                        zero += it == 0 ? 1 : 0;
                    }
                    dp[i][j] = (zero == 0 || zero == 4 ? 0 : dp[i][j]);
                }
            }
        }

//        for (var i : dp) {
//            for (var j : i) {
//                System.out.print(j + " ");
//            }
//            System.out.println();
//        }

        dp = binpow(dp, n, mod);

        long[][] base = new long[1][];
        base[0] = new long[sz];
        for (int i = 0; i < sz; i++){
            base[0][i] = 1;
        }

        base = mul(base, dp, mod);
        long ans = 0;
        for (int i = 0; i < sz; i++) {
            ans += base[0][i];
            ans %= mod;
        }

        System.out.println(ans);
    }

    public static long[][] mul(long[][] a, long[][] b, final long mod) {
        int n = a.length, m = b[0].length;
        long[][] res = new long[n][];
        for (int i = 0; i < n; i++) {
            res[i] = new long[m];
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < a[0].length; k++) {
                    res[i][j] += a[i][k] * b[k][j];
                    res[i][j] %= mod;
                }
            }
        }
        return res;
    }

    public static long[][] binpow(long[][] a, int n, final long mod) {
        long[][] res = new long[a.length][];
        for (int i = 0; i < a.length; i++) {
            res[i] = new long[a[i].length];
            for (int j = 0; j < a[i].length; j++) {
                res[i][j] = i == j ? 1 : 0;
            }
        }
        n--;
        while (n != 0) {
            if (n % 2 == 1) {
                res = mul(res, a, mod);
                n--;
            }
            a = mul(a, a, mod);
            n /= 2;
        }
        return res;
    }
}

import java.math.BigInteger;
import java.util.List;
import java.util.Scanner;

public class CutePatterns3 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        BigInteger n;
        int m, mod;

        n = input.nextBigInteger();
        m = input.nextInt();
        mod = input.nextInt();

        int sz = 1 << m;
        long[][] dp = new long[sz][];
        for (int i = 0; i < sz; i++) {
            dp[i] = new long[sz];
            for (int j = 0; j < sz; j++) {
                dp[i][j] = 1;
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

    public static long[][] binpow(long[][] a, BigInteger n, final long mod) {
        long[][] res = new long[a.length][];
        for (int i = 0; i < a.length; i++) {
            res[i] = new long[a[i].length];
            for (int j = 0; j < a[i].length; j++) {
                res[i][j] = i == j ? 1 : 0;
            }
        }
        n = n.subtract(BigInteger.ONE);
        while (n.compareTo(BigInteger.ZERO) != 0) {
            if (n.mod(BigInteger.TWO).equals(BigInteger.ONE)) {
                res = mul(res, a, mod);
                n = n.subtract(BigInteger.ONE);
            }
            a = mul(a, a, mod);
            n = n.divide(BigInteger.TWO);
        }
        return res;
    }
}

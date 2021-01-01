import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;
import java.util.concurrent.ThreadLocalRandom;

public class Gen {
    class DSU {
        int p[];
        int size[];
        int countComps;

        DSU(int n) {
            p = new int[n];
            size = new int[n];
            countComps = n;
            for (int i = 0; i < n; i++) {
                p[i] = i;
                size[i] = 1;
            }
        }

        int find(int v) {
            if (p[v] != v) {
                p[v] = find(p[v]);
            }
            return p[v];
        }

        void union(int v, int u) {
            v = find(v);
            u = find(u);
            if (v != u) {
                if (size[v] > size[u]) {
                    size[v] = size[v] + size[u];
                    p[u] = v;
                } else {
                    size[u] = size[u] + size[v];
                    p[v] = u;
                }
                countComps--;
            }
        }

        int size(int v) {
            return size[find(v)];
        }
    }

    static class Writer {
        PrintWriter cout;

        Writer() throws IOException {
            cout = new PrintWriter(System.out);
        }

        Writer(String name) throws IOException {
            cout = new PrintWriter(new FileWriter(name));
        }

        StringBuilder out = new StringBuilder();

        void print(Object a) {
            out.append(a);
        }

        void close() {
            cout.print(out.toString());
            cout.close();
        }
    }

    ThreadLocalRandom tlr = ThreadLocalRandom.current();
    static int n;
    static ArrayList<Integer> map;
    static Writer out;

    void help() {
        System.out.println("Generate isomorphic trees tool.\n" +
                "Keys: -1 - Generate random isomorphic trees\n" +
                "      -2 - Generate trees in style Ersh (Ezh)\n" +
                "      -3 - Generate binary trees\n" +
                "      -d - check for mapping vertex\n" +
                "Also you need write integer number - number of vertex.");
        System.out.flush();
    }

    static void checkUnmapped() {
        if (map != null) {
            for (int i = 0; i < n; i++) {
                if (map.get(i) == i) {
                    out.print("+ ");
                } else {
                    out.print("x ");
                }
                out.print(i + " " + map.get(i) + "\n");
            }
        }
    }

    int rand() {
        int r = tlr.nextInt();
        if (r < 0) {
            r = -r;
        }
        return r % n;
    }

    // Generate random isomorphic trees
    void run() throws IOException {
        DSU t = new DSU(n);
        ArrayList<Integer> F = new ArrayList<>(n - 1);
        ArrayList<Integer> S = new ArrayList<>(n - 1);
        while (t.countComps > 1) {
            int v = rand();
            int u = rand();
            if (t.find(v) != t.find(u)) {
                t.union(v, u);
                F.add(v);
                S.add(u);
            }
        }
        map = new ArrayList<>(n);
        for (int i = 0; i < n; i++) {
            map.add(i);
        }
        Collections.shuffle(map);
        out.print(n + "\n");
        for (int i = 0; i < n - 1; i++) {
            int v = F.get(i) + 1;
            int u = S.get(i) + 1;
            out.print(v + " " + u + "\n");
        }
        out.print("\n");
        for (int i = 0; i < n - 1; i++) {
            int v = F.get(i);
            int u = S.get(i);
            out.print((map.get(v) + 1) + " " + (map.get(u) + 1) + "\n");
        }
    }

    // Generate trees in style Ersh (Ezh)
    void run1() {
        out.print(n + "\n");
        for (int i = 1; i < n; i++) {
            out.print(i + " " + n + "\n");
        }
        out.print("\n");
        int v = n / 2;
        for (int i = 1; i < n + 1; i++) {
            if (v != i) {
                out.print(i + " " + v + "\n");
            }
        }
    }

    // Generate binary trees
    void run2() {
        int m = 1;
        while (m <= n) {
            m = m << 1;
        }
        n = m - 1;
        ArrayList<Integer> F = new ArrayList<>(n - 1);
        ArrayList<Integer> S = new ArrayList<>(n - 1);
        for (int i = 0; i < (n - 1) / 2; i++) {
            F.add(i);
            S.add(i * 2 + 1);
            F.add(i);
            S.add(i * 2 + 2);
        }
        map = new ArrayList<>(n);
        for (int i = 0; i < n; i++) {
            map.add(i);
        }
        Collections.shuffle(map);
        out.print(n + "\n");
        for (int i = 0; i < n - 1; i++) {
            int v = F.get(i) + 1;
            int u = S.get(i) + 1;
            out.print(v + " " + u + "\n");
        }
        out.print("\n");
        for (int i = 0; i < n - 1; i++) {
            int v = F.get(i);
            int u = S.get(i);
            out.print((map.get(v) + 1) + " " + (map.get(u) + 1) + "\n");
        }
    }

    public static void main(String[] args) throws IOException {
        boolean check = false;

        if (args.length == 0) {
            new Gen().help();
        }

        int treeType = 0;
        for (int i = 0; i < args.length; i++) {
            switch (args[i]) {
                case "-d":
                    check = true;
                    break;
                case "-1":
                    treeType = 1;
                    break;
                case "-2":
                    treeType = 2;
                    break;
                case "-3":
                    treeType = 3;
                    break;
            }
            if (args[i].charAt(0) >= '0' && args[i].charAt(0) <= '9') {
                n = Integer.parseInt(args[i]);
            }
        }

        out = new Writer();
        switch (treeType) {
            case 1:
                new Gen().run();
                break;
            case 2:
                new Gen().run1();
                break;
            case 3:
                new Gen().run2();
                break;
        }

        if (check) {
            checkUnmapped();
        }

        out.close();
    }
}
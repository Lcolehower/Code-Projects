
public class Main {

    public static double bisectionMethod(double a, double b) {
        double epsilon = 0.0001;
        double p = b + (a - b) / 2.0;

        while (Math.abs(Math.cos(p)) > epsilon) {
            if (Math.cos(a) * Math.cos(p) < 0) {
                b = p;
            } else {
                a = p;
            }
            p = b +(a - b) / 2.0;
        }

        return p;
    }

    public static void main(String[] args) {
        double a = 1.0;
        double b = 2.0;

        double root = bisectionMethod(a, b);
        System.out.println("Root found = " + root);

    }
}
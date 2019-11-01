public class Line {

    int start_x;
    int start_y;
    int end_x;
    int end_y;
    int R;
    int G;
    int B;

    public Line(int start_x, int start_y, int end_x, int end_y, int r, int g, int b) {
        this.start_x = start_x;
        this.start_y = start_y;
        this.end_x = end_x;
        this.end_y = end_y;
        R = r;
        G = g;
        B = b;
    }

    public int getStart_x() {
        return start_x;
    }

    public int getStart_y() {
        return start_y;
    }

    public int getEnd_x() {
        return end_x;
    }

    public int getEnd_y() {
        return end_y;
    }

    public int getR() {
        return R;
    }

    public int getG() {
        return G;
    }

    public int getB() {
        return B;
    }
}

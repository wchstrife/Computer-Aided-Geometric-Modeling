import java.awt.*;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.io.*;
import java.util.ArrayList;
import java.util.List;

//import com.spire.ms.System.Drawing.PointF;
import com.spire.pdf.FileFormat;
import com.spire.pdf.PdfDocument;
import com.spire.pdf.PdfPageBase;
import com.spire.pdf.graphics.PdfPen;
import com.spire.pdf.graphics.PdfRGBColor;


public class Solution {

    /*
    读取TXT当中的点和颜色
    返回一个线的list
     */
    public static List<Line> readFile(String filepath){

        List<Line> lines = new ArrayList<Line>();

        try{
            BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(filepath)));
            String lineTxt = null;
            while((lineTxt = br.readLine()) != null){
                String[] data = lineTxt.split(" ");
                int start_x = Integer.parseInt(data[0]);
                int start_y = Integer.parseInt(data[1]);
                int end_x = Integer.parseInt(data[0]);
                int end_y = Integer.parseInt(data[1]);
                int R = Integer.parseInt(data[2]);
                int G = Integer.parseInt(data[3]);
                int B = Integer.parseInt(data[4]);
                Line line = new Line(start_x, start_y,end_x,end_y, R, G, B);
                lines.add(line);
            }
        }catch (IOException e){
            e.printStackTrace();
        }

        return lines;
    }

    /*
    在PDF上画直线
     */
    public static void drawLine (List<Line> lines, String pdfPath, int pageNum) throws FileNotFoundException, IOException{
        PdfDocument doc = new PdfDocument();
        doc.loadFromFile(pdfPath);
        PdfPageBase page = doc.getPages().get(pageNum);
        if (page == null){
            System.out.println("page error!");
            return ;
        }
//        // 绘制直线
//        for (Line line : lines) {
//            PdfPen pen = new PdfPen(new PdfRGBColor(line.getR(), line.getG(), line.getB()), 0.1);
//            PointF pStart=new PointF(line.getStart_x(), line.getStart_y());
//            PointF pEnd=new PointF(line.end_x, line.getEnd_y());
//            page.getCanvas().drawLine(pen, pStart, pEnd);
//        }

        //绘制扇形
        float startAngle = 0;
        float sweepAngle = 270;
        PdfPen pen =new PdfPen(new PdfRGBColor(Color.black),0.1);
        Rectangle2D.Float rect4= new Rectangle2D.Float(70, 110, 50, 50);
        page.getCanvas().drawPie(pen, rect4, startAngle, sweepAngle);

        doc.saveToFile("done.pdf", FileFormat.PDF);
    }

    public static void main(String[] args) {
        String filepath = Solution.class.getResource("data.txt").getPath();     // 注意要获取编译后的data路径
        System.out.println(filepath);
        String pdfpath = "target.pdf";
        System.out.println(pdfpath);

        List<Line> lines = readFile(filepath);
        try{
            drawLine(lines, pdfpath, 1);
        }catch (Exception e){
            e.printStackTrace();
        }


        System.out.println("done!");
    }

}

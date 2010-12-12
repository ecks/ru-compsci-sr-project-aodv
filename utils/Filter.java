import java.io.*;
import java.util.Scanner;

public class Filter {
    public static void main (String ... args) {
        String use = "Use is: java Filter fileName ipAddress\n";
        String errmsg = "Errors: ";
        String fileStr = "";
        String ipToMatch = "";
        
        try {
            fileStr = args[0];
        } catch (ArrayIndexOutOfBoundsException ex) {
            errmsg += "No file supplied as argument.\n";
        }

        try {
            ipToMatch = args[1];
        } catch (ArrayIndexOutOfBoundsException ex) {
            errmsg += "No IP Address supplied as argument.\n";
        }

        try {
            File file = new File(fileStr);
            Scanner scan = new Scanner(file);
            String line, ip;

            while (scan.hasNext()) {
                line = scan.nextLine();
                if (!line.equals("=========================LAR UPDATE=========================")) {
                    continue;
                } else {
                    line = scan.nextLine();
                    ip = line.split(":")[1].trim();
                    if (ip.equals(ipToMatch)) {
                        System.out.println("=========================LAR UPDATE=========================");
                        System.out.println(line);
                        while (!line.equals("============================================================")) {
                            line = scan.nextLine();
                            System.out.println(line);
                        }
                    }
                }
            }
        } catch (FileNotFoundException ex) {
            errmsg += ("Bad filename given.\n");
        }

        if (!errmsg.equals("Errors: ")) {
            System.err.println(errmsg + use);
        }
    }
}
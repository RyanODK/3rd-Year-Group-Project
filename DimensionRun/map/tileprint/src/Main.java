import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Random;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        //sets path for file creation
        Path target = Paths.get("tile.txt");

        //initialize variables
        int x = 0;
        int y = 0;
        int tile = 5;
        String textForFile = "";
        try {
            //Enters for loop to create random numbers for each of the nodes and weights
            for (x = 0; x < 201; x++)
            {
                for(y = 0; y < 25; y++) {
                    if(y == 24)
                    {
                        tile = 0;
                    }
                    //Adds 3 values per line
                    textForFile += "TILE ";
                    textForFile += tile + " ";
                    textForFile += x + " ";
                    textForFile += y + " 0" + "\n";
                    tile = 5;
                }
            }
            //writes to file
            Files.write(target, textForFile.getBytes());
        } catch (IOException ex) {
            System.err.println(ex);
        }

    }
}
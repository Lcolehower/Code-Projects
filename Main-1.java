import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Hashtable;
import java.util.List;
import java.util.Map;

public class Main {

    public static class csvReader {
        public csvReader() {
        }

        public static HashMap<String, String> readAirports(String fileName) throws IOException {
            HashMap<String, String> airports = new HashMap<>();
            BufferedReader reader = new BufferedReader(new FileReader(fileName));

            String line;
            String location;
            String name;
            String code;

            // discard header
            if ((line = reader.readLine()) != null) {
                while ((line = reader.readLine()) != null) {
                    String[] tokens = line.split(",");
                    code = tokens[0];
                    name = tokens[1];
                    location = tokens[2] + ", " + tokens[3];

                    airports.put(code, name + ", " + location);
                }
            }

            return airports;
        }
    }

    public static void main(String[] args) throws IOException {


        HashMap<String, String> airports =
                csvReader.readAirports("C:\\Users\\Luked\\OneDrive\\Desktop\\Masters\\Essential Comp SCi 1\\Java\\assignment6\\Assignment 6 - IATA-airport-codes.csv");


        Hashtable<String, String> airports3 = new Hashtable<>(1009);


        HashTable<String, String> myAirports = new HashTable<>(1009);

        for(Map.Entry<String, String> airport : airports.entrySet()) {
            airports3.put(airport.getKey(), airport.getValue());
            myAirports.put(airport.getKey(), airport.getValue());
        }


        System.out.println(myAirports);
    }
}
package me.app;

import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Scanner;

import org.json.JSONArray;
import org.json.JSONObject;


public class Main {

	public static void main(String[] args) {
		String address = "http://api.openweathermap.org/data/2.5/weather?q=Bucharest,ro&appid=7b10426ee90376dc3d6525f847128b35&units=metric&format=json&lang=en";
		
		try {
			URL url = new URL(address);
			HttpURLConnection connection = (HttpURLConnection) url.openConnection();
			InputStream inputStream = connection.getInputStream();
			Scanner scanner = new Scanner(inputStream);
			StringBuilder stringBuilder = new StringBuilder();
			
			while(scanner.hasNextLine()) {
				stringBuilder.append(scanner.nextLine());
			}
			scanner.close();
			
			String response = stringBuilder.toString();
			//System.out.println(response);
			
			JSONObject json = new JSONObject(response);
			JSONArray weatherArray = json.getJSONArray("weather");
			JSONObject weatherObj = weatherArray.getJSONObject(0);
			String desc = weatherObj.getString("description");
			
			JSONObject main = json.getJSONObject("main");
			float temp = main.getFloat("temp");
			
			System.out.println("Temperature: " + (int)temp +"°C");
			System.out.println();
			System.out.println("Description: " + desc);
			
		}
		catch(Exception e) {
			e.printStackTrace();
		}
	}

}
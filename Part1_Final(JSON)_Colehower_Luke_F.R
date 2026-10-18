#Assignement 4 and Final Project
#A: Data Acquistion
library("httr")
library("jsonlite")
library("dplyr")


api_token <- "fyomrTSxVVehWDGloYuVWrNSXtDhWpTo"
url_handle <- "https://www.ncei.noaa.gov/access/services/data/v1"

station_ids <- c("USW00013897", "USW00026451", "USW00023183", "USW00053921", "USW00023174",
                 "USW00003017", "USW00054702", "USW00013773", "USW00012839", "USW00013874",
                 "USW00021504", "USW00024131", "USW00094846", "USW00093819", "USW00014933",
                 "USW00013996", "USW00093821", "USW00012916", "USW00014739", "USW00013752",
                 "USW00014615", "USW00094830", "USW00014922", "USW00013994", "USW00013957",
                 "USW00024033", "USW00013722", "USW00014914", "USW00094910", "USW00014764",
                 "USW00014734", "USW00023050", "USW00023169", "USW00094789", "USW00014821",
                 "USC00340260", "USW00024229", "USW00013739", "USW00014765", "USW00013875",
                 "USW00014944", "USW00013882", "USW00003927", "USW00024127", "USW00014742",
                 "USW00013743", "USW00024233", "USW00013888", "USC00470308", "USC00480027")
stations_ids_csv <- paste(station_ids, collapse = ",")
params <- list(
  dataset = "daily-summaries",
  stations = stations_ids_csv,
  startDate = "1974-01-01",
  endDate = "2024-06-30",
  datatypes = "TMAX,TMIN,PRCP,AWND,WT02,WT03,WT04,WT05",
  units = "standard",
  format = "json"
)
weather_list <- list()
response <- GET(url_handle, 
                query = params, 
                add_headers(token = api_token))
if(response$status_code == 200){
  mydf <- content(response, as = "text", encoding = "UTF-8")
  weather_json <- fromJSON(mydf, flatten = TRUE)
  weather_df <- as.data.frame(weather_json)
  print(head(weather_df))
  print("Data has been successfuly created")
}else{
  print(paste("Error:", response$status_code))
  print(content(response, "text"))
}

#B: EDA
library(ggplot2)
str(weather_df)
print(colnames(weather_df))
write.csv(weather_df, "weather_data_json.csv", row.names = FALSE)
sum(is.na(weather_df))
library(dataMaid)
makeDataReport(weather_df)


station_column_name <- "STATION"
if(station_column_name %in% colnames(weather_df)){
  missing_stations <- setdiff(station_ids, unique(weather_df[[station_column_name]]))
  print(paste("Stations with missing Data: ", paste(missing_stations, collapse = ", ")))
  ggplot(data.frame(station_ids = missing_stations), aes(x = station_ids, y = 1)) +
    geom_point(size = 5, color = "red") +
    labs(title = "Stations with Missing Data", x = "Station ID", y = " ") +
    theme(axis.text.x = element_text(angle = 45, hjust = 1))
} else {
  print(paste("Column", station_column_name, "not found in weather_df"))
}

temperature_column_name <- "TMAX" 

if (temperature_column_name %in% colnames(weather_df)) {
  weather_df[[temperature_column_name]] <- as.numeric(weather_df[[temperature_column_name]])
  summary(weather_df[[temperature_column_name]])
  
  ggplot(weather_df, aes(x = .data[[temperature_column_name]])) +
    geom_histogram(binwidth = 1, fill = "blue", color = "black", alpha = 0.5) +
    labs(title = "Temperature Distribution", x = "Temperature (Celsius)", y = "Frequency")+
    theme_minimal()
} else {
  print(paste("Column", temperature_column_name, "not found in weather_df"))
}
#C: Global Warming and Temperature Trends

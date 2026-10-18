#Import cvs file
murders$murder_rate <- (murder_rate = murders$total / murders$population * 100000)
average_murder_rate_by_region <- function(inputregion, filename){
  con <- file(filename, "a")
  region_data <- subset(murders, region == inputregion)
  avg_rate <- mean(region_data$murder_rate, na.rm = TRUE)
  
  cat("Summary Report for Region:", inputregion, "\n", file = con)
  cat("-----------------------------\n", file = con)
  cat("State        Average Murder Rate\n", file = con)
  cat("-----------------------------\n", file = con)
  for (i in 1:nrow(region_data)) {
    cat(sprintf("%-15s  %8.2f\n", region_data$state[i], region_data$murder_rate[i]), file = con)
  }
  cat("-----------------------------\n", file = con)
  cat("\nAverage Murder Rate:  ", avg_rate, "\n\n", file = con)
  close(con)
}
filename = "murders.csv"
dir <- system.file("extdata", package ="dslabs")
full.path <- file.path(dir, filename)
murders <- read.csv(full.path)
average_murder_rate_by_region("South", "Murder_rates_summary.txt")
average_murder_rate_by_region("West", "Murder_rates_summary.txt")
average_murder_rate_by_region("Northeast", "Murder_rates_summary.txt")
average_murder_rate_by_region("North Central", "Murder_rates_summary.txt")

#2 Read file
library(readr)
library(dplyr)
sale_data <- read.csv("C:/Users/Luked/Downloads/SalesData.csv", header = TRUE)

#3 Data Quality Analysis
class(sale_data)
typeof(sale_data)
duplicated_rows <- sale_data[duplicated(sale_data),]
unique(sale_data)
is.na(sale_data)
sum(is.na(sale_data))

#3B: Box Plot
boxplot(sale_data$Total.Profit)
boxplot(sale_data$Total.Revenue)
boxplot(sale_data$Total.Cost)
#3C: Verify Data
sale_data$Order.Date <- as.Date(sale_data$Order.Date, format = "%m/%d/%Y")
sale_data$Units.Sold <- as.integer(sale_data$Units.Sold)
sale_data$Item.type <- toupper(sale_data$Item.type)

#4 TIDY


#5 Data Analysis 
total_profit_by_region_Channel <- sale_data %>%
  group_by(Region, Sales.Channel)%>%
  summarize(Total_Profit = sum(Total.Profit, na.rm = TRUE))

sale_data$Year <- sale_data %>%
  mutate(Year = as.integer(format(Order.Date, "%Y")))

average_sales_by_sales <- sale_data %>%
  group_by(Year)%>%
  summarize(Average_Units_Sold = mean(Units.Sold, na.rm = TRUE))

average_profit_by_region <- sale_data %>%
  group_by(Region) %>%
  summarize(Average_Total_Profit = mean(Total.Profit, na.rm = TRUE))

total_revenue_by_item_type <- sale_data %>%
  group_by(Item.Type) %>%
  summarize(Total_Revenue = sum(Total.Revenue, na.rm = TRUE))
  
average_tota_Rev_by_Channel <- sale_data %>%
  group_by(Sales.Channel) %>%
  summarize(Average_Total_Revenue = mean(Total.Revenue, na.rm = TRUE))



#Load Data
data("airquality") 
View(airquality)

#Summary and Structure
summary(airquality)
str(airquality)
head(airquality)

#Missing Values
is.na(airquality)
sum(is.na(airquality))
colSums(is.na(airquality))

#Datatypes
str(airquality)
typeof(airquality)

#Duplication
duplicated_rows <- airquality[duplicated(airquality),]
print(duplicated_rows)


#Unique
unique(airquality)
unique(airquality$Ozone)
unique(airquality$Solar.R)
unique(airquality$Wind)
unique(airquality$Temp)
unique(airquality$Month)
unique(airquality$Day)

#outlines
boxplot(airquality$Ozone, main = "Ozone", ylab= "Ozone(ppb)", xlab = "Ozone", col = "blue")
boxplot(airquality$Solar.R, main = "Solar.R", ylab= "Solar.R", xlab = "Solar.R", col = "blue")
boxplot(airquality$Wind, main = "Wind", ylab= "Wind(MPH)", xlab = "Wind", col = "blue")
boxplot(airquality$Temp, main = "Tempature", ylab= "Temp(F)", xlab = "Temp", col = "blue")
boxplot(airquality$Month, main = "Month", ylab= "Month",  col = "blue")
boxplot(airquality$Day, main = "Day", ylab= "Days", col = "blue")

#Validty 
assertthat 
#Create Data Report
makeDataReport(airquality, output = "html")


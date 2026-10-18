#Part 1
#Install Required Packages
install.packages("dplyr")
install.packages("tidyverse")
install.packages("cat")
library(dslabs)
library(dplyr)
library(tidyverse)

#create Data Frame 
data("murders")
View(murders)
duplicated_rows <- murders[duplicated(murders),]
is.na(murders)
sum(is.na(murders))

#Creating Column murder_rate
murders$murder_rate <- (murder_rate = murders$total / murders$population * 100000)

#create Column Average Murder Rate by Region
average_murder_rate_by_region <- function(inputregion){
  region_data <- subset(murders, region == inputregion)
  avg_rate <- mean(region_data$murder_rate)
  
cat("Summary Report for Region:", inputregion, "\n")
cat("-----------------------------\n")
cat("State        Average Murder Rate\n")
cat("-----------------------------\n")
for (i in 1:nrow(region_data)) {
  cat(sprintf("%-15s  %8.2f\n", region_data$state[i], region_data$murder_rate[i]))
}
cat("-----------------------------\n")
cat("\nAverage Murder Rate:  ", avg_rate, "\n\n")
}
average_murder_rate_by_region("South")
average_murder_rate_by_region("West")
average_murder_rate_by_region("Northeast")
average_murder_rate_by_region("North Central")

#Part 2
#create column rate
murders <- murders %>%
  mutate(rate = total / population * 100000)

#Create column Rank
murders <- murders %>% 
  mutate(rank = rank(-rate))
murders%>% select(state, abb)
murders %>%top_n(5, -rate)

#Create Date_frame No South
no_south <- murders %>% 
  filter((region != "South"))
nrow(no_south)

#create murders_nw
murders_nw <- filter(murders, region %in% c("Northeast", "West"))
nrow(murders_nw)

#Create my states
my_state <- filter(murders, region %in% c("Northeast", "West") &
                     rate < 1)
select(my_state, state, rate, rank)

#Part 3
data(murders)
my_states <- murders %>%
  mutate(rate = total / population * 100, rank = rank(-rate))%>%
  filter(region %in% c("Northeast","West") & rate < 1)%>%
  select(state, rank, rate)
print(my_state)

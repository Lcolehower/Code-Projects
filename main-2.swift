//
//  main.swift
//  EnumerationsActivity_Colehower
//  Partner Imohimi Unuigbe
//  Created by Colehower, Luke Talbot on 10/28/24.
//

import Foundation

enum TempConverter {
    case Fahrenheit
    case Celsius

    // Initializer to set the operating mode based on a string input
    init(in scale: String) {
        switch scale.prefix(1).lowercased() {
        case "c":
            self = .Celsius
        case "f":
            self = .Fahrenheit
        default:
            self = .Celsius // Default to Celsius if input is invalid
        }
    }

    // Method to convert temperature based on the current scale
    func convert(for temp: Double) {
        switch self {
        case .Celsius:
            let fahrenheit = (temp * 9/5) + 32
            print("\(temp)°C is \(fahrenheit)°F")
        case .Fahrenheit:
            let celsius = (temp - 32) * 5/9
            print("\(temp)°F is \(celsius)°C")
        }
    }

    // Mutating function to switch between Celsius and Fahrenheit
    mutating func switchScale() {
        switch self {
        case .Celsius:
            self = .Fahrenheit
        case .Fahrenheit:
            self = .Celsius
        }
    }
}

// Demonstration of the TempConverter functionality
var myConverter = TempConverter(in: "Celsius")

// Convert well-known temperature values in Celsius
myConverter.convert(for: 100) // Boiling point
myConverter.convert(for: 0)   // Freezing point

// Switch to Fahrenheit
myConverter.switchScale()

// Convert the same temperatures now in Fahrenheit
myConverter.convert(for: 212) // Boiling point
myConverter.convert(for: 32)  // Freezing point
 

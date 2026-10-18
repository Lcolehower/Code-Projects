//
//  main.swift
//  Closures
// Partner Imohimi Unuigbe
//  Created by Colehower, Luke Talbot on 10/14/24.
//
import Foundation

// Function to check if a number is prime
func isPrime(_ number: Int) -> Bool {
    guard number >= 2 else {
        return false
    }
    if number == 2 {
        return true
    }
    if number % 2 == 0 {
        return false
    }
    let upperLimit = Int(sqrt(Double(number)))
    for i in stride(from: 3, through: upperLimit, by: 2) {
        if number % i == 0 {
            return false
        }
    }
    return true
}

// Function to check if a string can be converted to an integer
func isInt(_ entry: String) -> Bool {
    return Int(entry) != nil
}

// Function to read numbers and process them with the given closure
func readNumbers(using label: String, for process: (Int) -> Bool) {
    var totalEntries = 0
    var validCount = 0
    var invalidCount = 0
    var highestValid: Int? = nil
    var lowestValid: Int? = nil

    while true {
        print("Enter a number (or type 'exit' to finish):", terminator: " ")
        guard let input = readLine(), !input.isEmpty else { continue }

        if input.lowercased() == "exit" {
            break
        }

        guard isInt(input) else {
            print("Invalid entry, please enter an integer.")
            invalidCount += 1
            continue
        }

        let number = Int(input)!

        totalEntries += 1

        if process(number) {
            validCount += 1
            highestValid = highestValid.map { max($0, number) } ?? number
            lowestValid = lowestValid.map { min($0, number) } ?? number
            print("\(number) is \(label).")
        } else {
            invalidCount += 1
            print("\(number) is not \(label).")
        }
    }

    printResults(totalEntries: totalEntries, validCount: validCount, invalidCount: invalidCount, highestValid: highestValid, lowestValid: lowestValid, label: label)
}

// Function to print the results
func printResults(totalEntries: Int, validCount: Int, invalidCount: Int, highestValid: Int?, lowestValid: Int?, label: String) {
    print("\nTotal entries: \(totalEntries)")
    print("Total valid entries: \(validCount)")
    print("Total invalid entries: \(invalidCount)")

    if let highest = highestValid {
        print("Highest \(label) number entered: \(highest)")
    } else {
        print("Highest \(label) number entered: None")
    }

    if let lowest = lowestValid {
        print("Lowest \(label) number entered: \(lowest)")
    } else {
        print("Lowest \(label) number entered: None")
    }
}

// Running the prime test
readNumbers(using: "Prime", for: isPrime)

// Additional tests with closures
readNumbers(using: "Even", for: { $0 % 2 == 0 })
readNumbers(using: "Odd", for: { $0 % 2 != 0 })
readNumbers(using: "Multiple of 5", for: { $0 % 5 == 0 })


//
//  main.swift
//  primeFinder
//  Luke Colehower, Section 1
//  Partner Imohimi Unuigbe
//  Created by Colehower, Luke Talbot on 10/2/24.

import Foundation

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
    if upperLimit < 3 {
        return true
    }
   for i in stride(from: 3, through: upperLimit, by: 2) {
        if number % i == 0 {
            return false
        }
    }
    return true
}

class ProcessNumberCommand {
    private var totalEntries = 0
    private var primeCount = 0
    private var nonPrimeCount = 0
    private var highestPrime: Int? = nil
    private var lowestPrime: Int? = nil
   
    func execute(_ input: String) -> Bool {
        guard let doubleValue = Double(input), floor(doubleValue) == doubleValue else {
            print("Invalid entry, please enter an integer.")
            return true // Continue loop
        }
        let number = Int(doubleValue)
        if number == 0 {
            printResults()
            return false
        }
        totalEntries += 1
        if isPrime(number) {
            primeCount += 1
            highestPrime = highestPrime.map { max($0, number) } ?? number
            lowestPrime = lowestPrime.map { min($0, number) } ?? number
            print("\(number) is prime.")
        } else {
            nonPrimeCount += 1
            print("\(number) is non-prime.")
        }
       
        return true
    }
   
    private func printResults() {
        print("Total entries: \(totalEntries)")
        print("Total prime entries: \(primeCount)")
        print("Total non-prime entries: \(nonPrimeCount)")
       
        if let highest = highestPrime {
            print("Highest prime number entered: \(highest)")
        } else {
            print("Highest prime number entered: None")
        }
       
        if let lowest = lowestPrime {
            print("Lowest prime number entered: \(lowest)")
        } else {
            print("Lowest prime number entered: None")
        }
    }
}

let processCommand = ProcessNumberCommand()
while true {
    guard let input = readLine(), !input.isEmpty else { continue }
    if !processCommand.execute(input) {
        break
    }
}

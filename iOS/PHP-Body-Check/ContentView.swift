//
//  ContentView.swift
//  PHP-Body-Check
//
//  Created by Ilıa Prokhorov on 01.12.2023.
//

import SwiftUI
import SwiftData

struct ContentView: View {
    @State private var heightString: String = ""
    @State private var weightString: String = ""
    @State private var bmiString: String = "None"
    
    func calculateBMI() {
        let height = Double(heightString) ?? 0
        let weight = Double(weightString) ?? 0
        
        guard height > 0 && weight > 0 else {
            return
        }
        bmiString = BMICalculator.bmi(
            from: Int(height),
            weight: Int(weight)
        )
    }
    
    var body: some View {
        List {
            TextField(
                LocalizedStringKey("Height"),
                text: $heightString
            ).onChange(of: heightString) { oldValue, newValue in
                calculateBMI()
            }
            TextField(
                LocalizedStringKey("Weight"),
                text: $weightString
            ).onChange(of: weightString) { oldValue, newValue in
                calculateBMI()
            }
            Text(bmiString)
        }
    }
}

#Preview {
    ContentView()
}

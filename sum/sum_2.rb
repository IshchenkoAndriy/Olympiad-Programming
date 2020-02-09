
def allCombiantionsOfSumForNumber(resultNumber, numberOfVluesToAdd, availableNumbers)
	if resultNumber < 0 then
		return []
	end

	if numberOfVluesToAdd == 1 then
		return availableNumbers.include?(resultNumber) ? [[resultNumber]] : []
	end

	allCombiantion = []

	availableNumbers = availableNumbers.find_all { |number| number <= resultNumber }		# Remove all numbers bigger than resultNumber

	availableNumbers.each { |number|  
		availableNumbersForNestedCombinations = availableNumbers.find_all{ |available_number| available_number > number }
		nestedCombinations = allCombiantionsOfSumForNumber(resultNumber - number, numberOfVluesToAdd - 1,  availableNumbersForNestedCombinations)
		
		if not nestedCombinations.empty?
			allCombiantion.concat nestedCombinations.map { |nestedCombination| [number] + nestedCombination }
		end
	}

	allCombiantion
end

allAvailableNumbers = [0, 1, 2, 3, 4, 5, 6 ,7, 8, 9]
numberOfVluesToAdd = 3
originalNumber = 0
decimalSystemBase = 10

puts 'Find 3 numbers to sum'
puts '====================='
puts ''
puts 'Type a number with 3 or 4 digits: '

loop do
	originalNumber = gets.chomp.to_i
	break if originalNumber > 99 and originalNumber < 10000

	puts ' ...... Number must have 3 or 4 digits.'
	puts 'Type your namber again: '
end

beginning_time = Time.now

unitNumber = originalNumber.modulo decimalSystemBase
tensNumber = (originalNumber.modulo decimalSystemBase**2) / decimalSystemBase
hundredsAndThousandsNumber = (originalNumber.modulo decimalSystemBase**4) / decimalSystemBase**2

allCombiantionForUnits = []
numberOfVluesToAdd.times { |index| 
	allCombiantionForUnits.concat allCombiantionsOfSumForNumber(unitNumber + (index * decimalSystemBase), numberOfVluesToAdd, allAvailableNumbers)
}

allCombiantionForUnitsAndTens = []
allCombiantionForUnits.each { |unitCombinations|
	overflow = unitCombinations.inject(0){ |result, elem| result + elem } / 10
	availableNumbersForTens = allAvailableNumbers - unitCombinations

	allCombiantionForTens = []

	numberOfVluesToAdd.times { |index| 
		allCombiantionForTens.concat  allCombiantionsOfSumForNumber(tensNumber + (index * decimalSystemBase) - overflow, numberOfVluesToAdd, availableNumbersForTens)
	}
	
	if not allCombiantionForTens.empty?
		allCombiantionForTens.each { |tensCombinations| 
			allCombiantionForUnitsAndTens << [unitCombinations, tensCombinations]
		}
	end
}

allCombiantionForUnitsAndTensAndHundreds = []
allCombiantionForUnitsAndTens.each { |tensCombinations| 
	unitsOverflow = tensCombinations[0].flatten.inject(0){ |result, elem| result + elem } / 10 							# units items at index 0
	tensOverflow = (tensCombinations[1].flatten.inject(0){ |result, elem| result + elem } + unitsOverflow) / 10 		# tens items at index 1

	availableNumbersForHundreds = allAvailableNumbers - tensCombinations.flatten
	availableNumbersForHundreds.delete_if { |e| e <= 0 }

	allCombiantionForHundreds = allCombiantionsOfSumForNumber(hundredsAndThousandsNumber - tensOverflow, numberOfVluesToAdd, availableNumbersForHundreds)

	if not allCombiantionForHundreds.empty?
		allCombiantionForHundreds.each { |hundredsCombinations| 
			allCombiantionForUnitsAndTensAndHundreds << tensCombinations + [hundredsCombinations]
		}
	end
}

end_time = Time.now

puts '======================================================'
puts 'Hundreds and Thousands number: %d, Tens number: %d, Units number: %d' % [hundredsAndThousandsNumber, tensNumber, unitNumber]

if allCombiantionForUnitsAndTensAndHundreds.empty?
	puts 'For this number there is no solutions!'
else
	puts "For this number there are #{allCombiantionForUnitsAndTensAndHundreds.count * 6**3} solutions!"
end
allCombiantionForUnitsAndTensAndHundreds.each_with_index { |combination, index|
	puts '%d: %s' % [index, combination.inspect]
}

# totalIndex = 0
# allCombiantionForUnitsAndTensAndHundreds.each{ |combination|
# 	unitsCombination = combination[0]
# 	tensCombination = combination[1]
# 	hundredsCombination = combination[2]

# 	unitsCombination.count.times { |index| 
# 		tensCombination.count.times { |index| 
# 			hundredsCombination.count.times { |index| 
# 				puts '%d: %d + %d + %d' % [totalIndex, combination.inspect]
# 				totalIndex++
# 			}
# 		}
# 	}
# }

puts "Time elapsed #{(end_time - beginning_time)}"

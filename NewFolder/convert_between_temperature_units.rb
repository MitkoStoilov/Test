def convert_between_temperature_units(x, a, b)
	if a == 'C' && b == 'K'
		x = x + 273.15

	elsif a == 'C' && b == 'F'
		x = 32.00 + x*1.80

	elsif a == 'F' && b == 'K'
		x = (x - 32.00)/1.80 + 273.15

	elsif a == 'F' && b == 'C'
		x =  (x-32.00)/1.80

	elsif a == 'K' && b == 'C'
		x = x - 273.15

	elsif a == 'K' && b == 'F'
		x = (x + 32.00)*1.80 - 273.15

	elsif a == b
		x

	end

end


puts convert_between_temperature_units(1, 'C', 'C')


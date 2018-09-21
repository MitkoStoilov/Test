#!/Documents/ruby ruby
class MegaGreeter
	attr_accessor :names

	def initialize(names = "World")
		@names = names
	end

	def say_hi
		if @names == nil
			puts "..."

		elsif @names.respond_to?("each")
			@names.each do |name|
			puts "Hello #{name}!"
		end
		else
			puts "Hello #{@names}"
		end
	end

	def say_bye
		if @names == nil
			puts "..."
		
		elsif @names.respond_to?("join")
			puts "Goodbye #{@names.join(", ")}. Come back soon!"
		end
	end
end

if __FILE__ == $0

	mg = MegaGreeter.new
	mg.say_hi
	mg.say_bye

	mg.names = "Zeke"
	mg.say_hi
	mg.say_bye

	mg.names = ["Mitko", "Sam", "Paco", "Dimo"]
	
	mg.say_hi
	mg.say_bye

	mg.names = nil
	mg.say_hi
	mg.say_bye
	end
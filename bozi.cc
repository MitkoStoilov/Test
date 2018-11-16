#include<iostream>

using namespace std;

class ListOfArrays {

    class ArrayNode {

        public:

        
        int size_;
        int* data_;
        ArrayNode* prev_;
        ArrayNode* next_;

        ArrayNode(int* data, int size)
            : data_(data), size_(size), next_(0), prev_(0) {
                data_=new int[size];
            }

        ~ArrayNode() {
            delete [] data_;
        }
        int push_a(int val){
            data_++;
            *data_ = val;
            
        }

    };

    ArrayNode* head_;
    int size_;

    public:

    class Iterator {

        friend class ListOfArrays;

        ListOfArrays& list_;
        ArrayNode* current_;

        public:

        Iterator(ListOfArrays& list, ArrayNode* current)
            : list_(list), current_(current) {}

        bool operator==(const Iterator& other){
            return current_ == other.current_;
        }

        bool operator!=(const Iterator& other){
            return ! operator == (other);
        }

        Iterator& operator++(){
            current_ = current_ -> next_;
            return *this;
        }

        Iterator operator++(int){
            Iterator res(list_, current_);
            current_ = current_ -> next_;
            return res;
        }

        int& operator[](const int& index){
            int& a = current_->data_[index-current_->size_+1];
            return a;
        }

        int size(){
            return current_->size_;
        }

        void show(){
            for(int i = 0;i<this->size();i++){
                cout << current_->data_[i-current_->size_+1] << ' ';
            }
            cout << endl;
        }
        
        double average(){
            double a=0;
            for(int i = 0;i<this->size();i++){
                a += current_->data_[i-current_->size_+1];
            }
            a = a/this->size();
            //cout << a << endl;
            return a;
        }
        
        double median(){
            double m = 0;
            int v;
            int c;
            if(this->size()%2==0){
                v = this->size()/2;
                c = v--;
                m = current_->data_[v-current_->size_+1] + current_->data_[c-current_->size_+1];
                m=m/2;
            }else{
               v = this->size()/2;
               m = current_->data_[v-current_->size_+1]; 
            }
            //cout << m<<endl;
            return m;
        }
        
        int sum(){
            int sum=0;
            for(int i = 0;i<this->size();i++){
                sum += current_->data_[i-current_->size_+1];
            }
            //cout << sum <<endl;;
            return sum;
        }
        
        Iterator& ordered(bool ascending = true){
            int i, j, c; 
            bool swapped;
            if(ascending){
                for (i = 0; i < this->size()-1; i++) 
                { 
                    swapped = false; 
                    for (j = 0; j < this->size()-i-1; j++) 
                    { 
                        if (current_->data_[j-current_->size_+1] > current_->data_[j-current_->size_+1+1]) 
                        { 
                            c = current_->data_[j-current_->size_+1];
                            current_->data_[j-current_->size_+1] = current_->data_[j-current_->size_+1+1];
                            current_->data_[j-current_->size_+1+1] = c;
                            swapped = true; 
                        } 
                    } 
                    if (swapped == false) 
                        break; 
                }
            }else{
                for (i = 0; i < this->size()-1; i++) 
                { 
                    swapped = false; 
                    for (j = 0; j < this->size()-i-1; j++) 
                    { 
                        if (current_->data_[j-current_->size_+1] < current_->data_[j-current_->size_+1+1]) 
                        { 
                            c = current_->data_[j-current_->size_+1];
                            current_->data_[j-current_->size_+1] = current_->data_[j-current_->size_+1+1];
                            current_->data_[j-current_->size_+1+1] = c;
                            swapped = true; 
                        } 
                    } 
                    if (swapped == false) 
                        break; 
                }
            }       
            return *this;
        }
    };

    ListOfArrays()
            : size_(0), head_(new ArrayNode(0, 0)) {
        head_->next_ = head_;
        head_->prev_ = head_;
    }

    ~ListOfArrays(){
       // cout << "hi" << endl;
    }

    ListOfArrays(const ListOfArrays& other)
    		: size_(0), head_(new ArrayNode(0, 0)) {
    	head_->next_ = head_;
        head_->prev_ = head_;
        ArrayNode* node = other.head_->next_;

        while (node != other.head_){
            push(node->data_, 1-node->size_, node->size_);
            node = node->next_;
        }
    		
    }

    ListOfArrays& operator=(const ListOfArrays& other);

    int size(){
        return size_;
    }

    void push(int array[], int position, int length){
        int size = position + length;
        int data[length]; 
        int z =0;

        ArrayNode* element = new ArrayNode(data, length);

        for(int i = position; i<size; i++){

            data[z] = array[i];
            element->push_a(data[z]);
            z++;
            //cout << element->data_[0];
        }
        
        ArrayNode* last_element = head_->prev_;

        last_element->next_ = element;
        element->prev_ = last_element;

        element->next_ = head_;
        head_->prev_ = element;

        size_++;
        //cout << element->data_[2]<<endl;;
    }

    void averages(double averages[]);

    void medians(double medians[]);
    
    void sizes(int sizes[]);
    
    void sums(int sums[]);

    Iterator begin(){
        return Iterator(*this, head_->next_);
    }

    Iterator end(){
        return Iterator(*this, head_);
    }

    ListOfArrays& ordered(bool ascending = true){
    	//bool asc = ascending;
    	int count = 0;
    	bool swapped;

    	for(ListOfArrays::Iterator it = this->begin();it != this->end(); it++){
    		it.ordered(ascending);
    	}
    	ListOfArrays::Iterator it1 = this->begin();

    	while(true){
    		swapped = false;
    		count++;
	    	for(ListOfArrays::Iterator it = this->begin();it != this->end(); it++){
	    		it1.current_ = it.current_;
	    		it1++;
	    		if(it1==this->end()){
	    			break;
	    		}
	    		//it.show();
		   		//it1.show();
		   		if(ascending == false){
			   		if(it.sum() < it1.sum()){

			   				ListOfArrays::Iterator it2 = this->begin();

			   				it.current_-> prev_-> next_ = it1.current_;
			    			it1.current_-> next_-> prev_ = it.current_;

			   				it.current_->next_ = it1.current_->next_;
			    			it1.current_->prev_ = it.current_->prev_;

			    			it.current_->prev_ = it1.current_;
			    			it1.current_->next_ = it.current_;

			    			it2.current_ = it1.current_;
			    			it1.current_ = it.current_;
			    			it.current_ = it2.current_;

			    			swapped = true;	
			    	}
			    }else{
			    	if(it.sum() > it1.sum()){

			   				ListOfArrays::Iterator it2 = this->begin();

			   				it.current_-> prev_-> next_ = it1.current_;
			    			it1.current_-> next_-> prev_ = it.current_;

			   				it.current_->next_ = it1.current_->next_;
			    			it1.current_->prev_ = it.current_->prev_;

			    			it.current_->prev_ = it1.current_;
			    			it1.current_->next_ = it.current_;

			    			it2.current_ = it1.current_;
			    			it1.current_ = it.current_;
			    			it.current_ = it2.current_;

			    			swapped = true;	
			    	}
			    }
		    	//cout << swapped<<endl;;
	    	}
	    	if(swapped == false){
	    		break;
	    	}
	    }
	    //cout << count << endl;
    	return *this;
    }

    ListOfArrays& operator*=(const int& coef);

    ListOfArrays& operator+=(const int& value);

    void show(){
        int i = 0;
        for(ListOfArrays::Iterator it = this->begin();it != this->end(); it++){
            int a = it.size();
            a -= 1;
            bool flag = 0;
            i++;
            if(i == this->size()){
                flag = 1;
            }
            for(int i = 0; i<it.size();i++){
                
                if(i == a && flag == 0){
                    cout << it[i] << "; ";
                }else{
                    cout << it[i] << ' ';
                }
            }
        }
        cout << endl;
    }
};

int main(){

    ListOfArrays l;

    int ARR[17] = {4, 7, 3, 2, 1, 5, 6, 9, 4, 4, 5, 6, 9, 10, 45, 10, 13};
    //cout << l.size() << endl;
    l.push(ARR, 0, 5);
    l.push(ARR, 5, 4);
    l.push(ARR, 9, 8);
    //cout << l.size() << endl;
    /*ListOfArrays::Iterator it = l.begin();

    cout << it.size() << endl;
    cout << it[0]<<endl;

    ListOfArrays::Iterator it1 = l.end();
    cout << it1.size() << endl;
    cout << it1[0]<<endl;*/
    /*for(ListOfArrays::Iterator it = l.begin();it != l.end(); it++){
        for(int i = 0; i<it.size();i++){
            cout << it[i] << ' ';
        }
        cout << endl;
        cout<< "it.size()= "<< it.size() << endl;
    }*/
    ListOfArrays d = l;
    d.show();
    d.ordered(false);
    d.show();
    ListOfArrays::Iterator it = l.begin();
    //it++;
    //it++;
    //it.show();
    //it.ordered(false);
    //it.show();
    //it.average();
    //it.median();
    //it.sum();

    return 0;
}

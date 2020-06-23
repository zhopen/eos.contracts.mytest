#include <eosio/eosio.hpp>
#include <eosio/print.hpp>


using namespace eosio;

class hello : public contract {
  public:
    using contract::contract;
     
    [[eosio::action]]
    void hi( name user ) {
	    require_auth(user);
	    print("get_first_receiver()=", get_first_receiver());

		print( "Hello, ", name{user});
    	//eosio_assert(1, "哈啊哈{ab,c,c,c,c,c,c,}");
      }
	  
	[[eosio::action]]
     void hiself() {
		require_auth(_self);
		print( "Hello, ", _self.to_string());

   }
   
   	[[eosio::action]]
     void hiany() {
		print( "Hello, ", _self.to_string());
   }
};
//EOSIO_DISPATCH( hello, (hi)(hi2))


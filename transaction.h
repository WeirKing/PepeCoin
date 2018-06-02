
#ifndef __transaction__
#define __transaction__

#include        <stdio.h>               /* printf() and fprintf() */
#include        <stdlib.h>              /* for atoi() and exit() */
#include        <arpa/inet.h>           /* for sockaddr_in and inet_ntoa() */
#include        <sys/types.h>
#include        <unistd.h>
#include        "crypto_util.cpp"

/*
 * A transaction in theory is the public key of the current owner, a hash of the pub key of current owner 
        and the previous transaction data signed with the private key of the past owner
 * There's three data fields in actuality, hash of the previous transaction, the public key of the owner, and the signature of both. 
 * We will also track the previous transaction and the next transaction in a doubly linked list format. 
 * If we ever need want to prune previous transactions we need just traverse the list back in time 
        and clear out previous transactions.
 * If a transaction has no previous transaction that means it was either a new bitcoin released or a 
        transaction that had its previous transactions pruned. 
 * We cannot verify this transaction with checking the relevant block. 
 */

class Transaction{
public:
    string signed_hash;
    string public_key;
    string prev_hash;
    Transaction *previous_transaction;
    Transaction();
    Transaction(string new_owner, Transaction *prev_t, string private_key);//Creates a new transaction in full
    Transaction(string new_owner, Transaction *prev_t);
    bool verify_transaction(Transaction *prev);
    friend std::ostream& operator<<(std::ostream& os, const Transaction& s);
    friend std::istream& operator>>(std::istream& is, Transaction& s);
    
private:
    void set_hash(Transaction *prev);
    void sign_hash(string private_key);

/*
 * Output this transaction and all previous transactions to a file
 */
    friend std::ostream& operator<<(std::ostream& os, const Transaction& s)
    {
        os << s.prev_hash << endl;
        os << s.signed_hash << endl;
        os << s.public_key << endl;
        return os;
    }

/*
 * Input this transaction and all previous transactions from a file
 */
    friend std::istream& operator>>(std::istream& is, Transaction& s)
    {
        is >> s.prev_hash;
        is >> s.signed_hash;
        is >> s.public_key;
        return is;

    }
};

/*
 * Sets the hash for this transaction based on the previous 
 */
void Transaction::set_hash(Transaction *prev)
{
    crypto::hash_transaction(prev->public_key + prev->prev_hash + prev->signed_hash, prev_hash);
}

/*
 * Signs the hash with the supplied private key
 */
void Transaction::sign_hash(string private_key)
{
    crypto::sign_hash(prev_hash, private_key, signed_hash);
}

/*
 * Verifies that the transaction is valid based on the set previous transaction. Previous transaction is 100% trusted.
 * Previous transaction must be set first before calling this function
 */
bool Transaction::verify_transaction(Transaction *prev){
    string prev_pub_key = prev->public_key;
    string real_prev_hash;
    string info = prev->signed_hash + public_key + prev_hash;
    crypto::hash_transaction(info, real_prev_hash);
    if (real_prev_hash != prev_hash){
        return false;
    }
    
    crypto::verify_signature(signed_hash, real_prev_hash, public_key);
    return true;
}

Transaction::Transaction(string new_owner, Transaction *prev_t){
    previous_transaction = prev_t;
    public_key = new_owner;
    set_hash(prev_t);
}

#endif

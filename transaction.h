#include        <stdio.h>               /* printf() and fprintf() */
#include        <stdlib.h>              /* for atoi() and exit() */
#include        <arpa/inet.h>           /* for sockaddr_in and inet_ntoa() */
#include        <sys/types.h>
#include        "pepe_miner.util"       /* utility funcions for pepe miner */
#include        <unistd.h>

/*
 * A transaction in theory is the public key of the current owner, a hash of the pub key of current owner 
        and the previous transaction data signed with the private key of the past owner
 * There's two data fields in actuality, the signed hash, and the pub key of current owner. 
 * We will also track the previous transaction and the next transaction in a doubly linked list format. 
 * If we ever need want to prune previous transactions we need just traverse the list back in time 
        and clear out previous transactions.
 * If a transaction has no previous transaction that means it was either a new bitcoin released or a 
        transaction that had its previous transactions pruned. 
 * We cannot verify this transaction with checking the relevant block. 
 */

class Transaction{
public:
    uint64_t signed_hash;
    uint64_t public_key;
    Transaction *previous_transaction;
    Transaction *next_transaction;


/*
 * Output this transaction and all previous transactions to a file
 */
    friend std::ostream& operator<<(std::ostream& os, const Transaction& s)
    {
        os << s.signed_hash << endl;
        os << s.public_key << endl;
        if (s.previous_transaction == NULL){
            os << 'Z' << endl;
        } else {
            os << *(s.previous_transaction);
        }
        return os;
    }

/*
 * Input this transaction and all previous transactions from a file
 */
    friend std::istream& operator>>(std::istream& is, Transaction& s)
    {
        is >> s.signed_hash;
        is >> s.public_key;
        is.get();
        if (is.get() == 'Z'){
            s.previous_transaction = NULL;
            int a;
            is >> a;
        } else {
            is.unget();
            Transaction *new_transaction = new Transaction;
            s.previous_transaction = new_transaction;
            new_transaction->next_transaction = &s;
            is >> *new_transaction;
        }
        return is;

    }

    void set_hash(uint64_t new_owner, uint64_t owner_private_key){
        
    }
};


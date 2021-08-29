/*
Да се дефинира апстрактна класа User за која ќе се чуваат:

username (char[50])
password (char[50])
email (char[50])
Класата треба да содржи еден чист виртуелен метод double popularity().

Од оваа класа да се изведат две класи и тоа FacebookUser и TwitterUser.

За класата FacebookUser уште се чуваат и:

број на пријатели
број на лајкови и
број на коментари
Популарноста се пресметува така што се собираат бројот на пријатели, бројот на лајкови и бројот на коментари, но притоа бројот на лајкови се множи со коефициент на вредност на лајкот кој е ист за секој корисник и изнесува 0.1, а исто така и бројот на коментари се множи со ист таков коефициент кој е 0.5.

За класата TwitterUser уште се чуваат и:

број на следачи и
број на твитови
Популарноста се пресметува така што се собираат бројот на следачи и бројот на твитови, но притоа бројот на твитови се множи со коефициент на вредност на твитот кој е ист за секој корисник и изнесува 0.5.

Да се креира класа SocialNetwork која ќе содржи:

динамичка низа од покажувачи од класата User
број на тековни корисници и
максимален број на корисници кој може да го содржи мрежата и кој е ист за сите мрежи и иницијално е поставен на 5
Да се преоптовари операторот += со кој ќе се додава нов корисник.

Да се дефинира метод avgPopularity() кој ќе ја враќа просечната популарност на корисниците во мрежата.

Исто така да се овозможи промена на максималната големина на низата преку методот changeMaximumSize(int number).

Потребно е да се справите со следните исклучоци:

Доколку лозинката на корисникот не содржи барем 1 голема буква, 1 мала буква и 1 број да се фрли исклучок од класа InvalidPassword така што како параметар ќе се прати пораката Password is too weak.
Доколку емаилот на корисникот не содржи точно еднаш @ да се фрли исклучок од класа InvalidEmail така што како параметар ќе се прати пораката Mail is not valid.
Доколку проба да се додаде корисник во социјалната мрежа, а веќе максималниот број на корисници е пополнет да се фрли исклучок од класа MaximumSizeLimit така што како параметар ќе се прати максималниот број на корисници во мрежата.
Сите класи кои се справуваат со исклучоци треба да го имаат имплементирано методот void message() така што за првите две класи ќе ја печати пораката којашто е испратена како параметар, а за последната класа ќе печати You can't add more than N users, каде што N е параметарот кој е пратен. Исто така со try-catch блокови справете се со исклучоците на соодветните места во main(), каде што во catch ќе го повикате методот message() од соодветниот исклучок.
*/
#include <iostream>
#include <cstring>

using namespace std;

class InvalidPassword
{
private:
    char error[50];
public:
    InvalidPassword(char *error)
    {
        strcpy(this->error, error);
    }

    void message()
    {
        cout << error << endl;
    }
};

class InvalidMail
{
private:
    char error[50];
public:
    InvalidMail(char *error)
    {
        strcpy(this->error, error);
    }

    void message()
    {
        cout << error << endl;
    }
};

class MaximumSizeLimit
{
private:
    int n;
public:
    MaximumSizeLimit(int n)
    {
        this->n = n;
    }

    void message()
    {
        cout << "You can't add more than " << n << " users." << endl;
    }
};

class User
{
protected:
    char username[50];
    char password[50];
    char email[50];

    void setPassword(char *password = "")
    {
        bool lowercase = false;
        bool uppercase = false;
        bool number = false;

        for (int i = 0; i < strlen(password); i++)
            if (isupper(password[i]))
                uppercase = true;
            else if (islower(password[i]))
                lowercase = true;
            else if (isdigit(password[i]))
                number = true;

        if (lowercase && uppercase && number)
            strcpy(this->password, password);
        else
            throw InvalidPassword("Password is too weak.");
    }

    void setEmail(char *email = "")
    {
        int at = 0;

        for (int i = 0; i < strlen(email); i++)
            if (email[i] == '@')
                at++;

        if (at == 1)
            strcpy(this->email, email);
        else
            throw InvalidMail("Mail is not valid.");
    }

public:
    User(char *username = "", char *password = "", char *email = "")
    {
        strcpy(this->username, username);
        setPassword(password);
        setEmail(email);
    }

    virtual double popularity() = 0;
};

class FacebookUser : public User
{
private:
    int friends;
    int likes;
    int comments;
    static double likes_ratio;
    static double comments_ratio;
public:
    FacebookUser(char *username = "", char *password = "", char *email = "", int friends = 0, int likes = 0,
                 int comments = 0) : User(username, password, email)
    {
        this->friends = friends;
        this->likes = likes;
        this->comments = comments;
    }

    double popularity()
    {
        return friends + likes_ratio * likes + comments_ratio * comments;
    }
};

double FacebookUser::likes_ratio = 0.1;
double FacebookUser::comments_ratio = 0.5;

class TwitterUser : public User
{
private:
    int followers;
    int tweets;
    static double tweets_ratio;
public:
    TwitterUser(char *username = "", char *password = "", char *email = "", int followers = 0, int tweets = 0) : User(
            username, password, email)
    {
        this->followers = followers;
        this->tweets = tweets;
    }

    double popularity()
    {
        return followers + tweets_ratio * tweets;
    }
};

double TwitterUser::tweets_ratio = 0.5;

class SocialNetwork
{
private:
    User **u;
    int n;
    static int max;
public:
    SocialNetwork()
    {
        u = new User *[0];
        n = 0;
    }

    ~SocialNetwork()
    {
        delete[] u;
    }

    SocialNetwork &operator+=(User *user)
    {
        if (n == max)
            throw MaximumSizeLimit(max);

        User **temp = new User *[n + 1];

        for (int i = 0; i < n; i++)
            temp[i] = u[i];
        temp[n] = user;

        n++;
        delete[] u;
        u = temp;

        return *this;
    }

    static void changeMaximumSize(int number)
    {
        max = number;
    }

    double avgPopularity()
    {
        double s = 0;

        for (int i = 0; i < n; i++)
            s += u[i]->popularity();

        return s / n;
    }
};

int SocialNetwork::max = 5;

int main()
{

    SocialNetwork network = SocialNetwork();
    int n;
    cin >> n;
    char username[50];
    char password[50];
    char email[50];
    int userType;
    for (int i = 0; i < n; ++i)
    {
        cin >> username;
        cin >> password;
        cin >> email;
        cin >> userType;
        if (userType == 1)
        {
            int friends;
            int likes;
            int comments;
            cin >> friends >> likes >> comments;

            try
            {
                User *u = new FacebookUser(username, password, email, friends, likes, comments);
                network += u;
            }
            catch (InvalidPassword &i)
            {
                i.message();
            }
            catch (InvalidMail &i)
            {
                i.message();
            }
            catch (MaximumSizeLimit &i)
            {
                i.message();
            }
        }
        else
        {
            int followers;
            int tweets;
            cin >> followers >> tweets;

            try
            {
                User *u = new TwitterUser(username, password, email, followers, tweets);
                network += u;
            }
            catch (InvalidPassword &i)
            {
                i.message();
            }
            catch (InvalidMail &i)
            {
                i.message();
            }
            catch (MaximumSizeLimit &i)
            {
                i.message();
            }
        }

    }
    network.changeMaximumSize(6);
    cin >> username;
    cin >> password;
    cin >> email;
    int followers;
    int tweets;
    cin >> followers >> tweets;

    try
    {
        User *u = new TwitterUser(username, password, email, followers, tweets);
        network += u;
    }
    catch (InvalidPassword &i)
    {
        i.message();
    }
    catch (InvalidMail &i)
    {
        i.message();
    }
    catch (MaximumSizeLimit &i)
    {
        i.message();
    }

    cout << network.avgPopularity();

}

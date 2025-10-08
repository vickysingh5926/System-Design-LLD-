#include <bits/stdc++.h>
using namespace std;
 
enum class City{Bangalore, Delhi};
enum  class SeatCategory{SILVER, GOLD,PLATINUM};

class Seat{
    public:
    int seatId;
    int row;
    SeatCategory seatCategory;

    Seat(){}
    Seat(int id, SeatCategory category):
    seatId(id),seatCategory(category),row(0){}
};

class Movie{

    public:
    int movieId;
    string movieName;
    int movieDuration;
    Movie(){}
    Movie(int id,string name,int duration):
    movieId(id),movieName(name),movieDuration(duration){}
};

class Payment{
    public:
    int paymentId;
};

class Screen;
class Show;

class Booking{

    public:
    Show* show;
    vector<Seat>bookedSeats;
    Payment payment;

    void setShow(Show* s){show=s;}
    void setBookedSeats(vector<Seat>&seats){bookedSeats=seats;}
};

class Screen{
    public:
    int screenId;
    vector<Seat>seats;

    void setScreenId(int id){
        screenId=id;
    }
    void setSeats(const vector<Seat>&s){
        seats=s;
    }
};

class Show{

    public:
    int showId;
    Movie* movie;
    Screen* screen;
    int showStartTime;
    vector<int>bookedSeatId;

    Show(): movie(nullptr),screen(nullptr),showStartTime(0){}

    void setShowId(int id){showId=id;}
    void setMovie(Movie* m){movie=m;}

    void setScreen(Screen * s){screen=s;}
    void setShowStartTime(int time){showStartTime=time;}
    vector<int>&getBookedSeatIds(){return bookedSeatId;}

};

class Theatre{

    public:
    int threatId;
    string address;
    City city;
    vector<Screen>screens;
    vector<Show>shows;

    void setTheatreId(int id){theatreId=id;}
    void setCity(City c){city=c;}
    void setScreens(const vector<Screen>&s){screen=s;}
    void setShows(const vector<Show>&s){shows=s;}

    vector<Screen>&getScreen(){return screens;}
    vector<Show>&getShows(){return shows;}

};

class MovieController{
    public:
    map<City,vector<Movie>>cityVsMovies;
    vector<Movie>allMovies;

    void addMovie(const Movie& movie,City city){
        allMovies.push_back(movie);
        cityVsMovies[city].push_back(movie);
    }
    Movie* getMovieByName(const string& movieName){

        for(auto& movie : allMovies){
            if(movie.movieName==movieName)
            retune &movie;
        }
        return nullptr;
    }
    vector<Movie>getMoviesByCity(City city){
        return cityVsMovies[city];
    }
};

class TheatreController{

    public:
    map<City,vector<Theatre>>cityVsTheatre;
    vector<Theatre>allTheatre;
    
    void addTheatre(const Theatre& theatre, City city){
        allTheatre.push_back(theatre);
        cityVsTheatre[City].push_back(theatre);
    }

    map<Theatre*,vector<Show*>>getAllShow(Movie* movie, City city){
        
        map<Theatre*,vector<Show*>>theatreVsShows;
        auto &theatres=cityVsTheatre[city];

        for(auto &theatre:theatres){
            vector<Show*>givenMovieShow;
            for(auto &show:theatre.shows){
                if(show.movie->movieId==movie->movieId)
                givenMovieShow.push_back(&show);
            }

            if(!givenMovieShow.empty()){
                theatreVsShows[&theatre]=givenMovieShow;
            }
        }

        return theatreVsShows;
    }
};

class BookMyShow{
    public:
    MovieController movieController;
    TheatreController theatreController;

    BookMyShow(){}

    void intialize(){
        createMovies();
        createTheatre();
    }
    void createBooking(City userCity,const string & movieName){

        vector<Movie>movies=movieController.getMoviesByCity(userCity);
         Movie* interestedMovie=nullptr;
         for(auto& movie:movies){
            if(movie.movieName==movieName){
                interestedMovie=&movie;
                break;
            }
         }

         if(!interestedMovie){
            cout<<"Movie not found in your city"<<endl;
            return;
        }

      auto showsTheatreWise=theatreController.getAllShow(interestedMovie,userCity);

      if(showsTheatreWise.empty()){

        cout<<"No shows available"<<endl;
        return ;
      }

      auto firstTheatre=showsTheatreWise.begin()->first;
      auto runningShows=showsTheatreWise.begin()->second;

      Show* interestedShow=runningShows[0];

      int seatNumber=30;
      auto& bookedSeats=interestedShow->getBookedSeatIds();

      if(find(bookedSeats.begin(),bookedSeats.end(),seatNumber)==bookedSeats.end()){
        bookedSeats.push_back(seatNumber);

        Booking booking;
        vector<Seat>myBookedSeats;

        for(auto& screenSeat: interestedShow->screen->seats){
            if(screenSeat.seatId==seatNumber)
            myBookedSeats.push_back(screenSeat);
        }

        booking.setBookedSeats(myBookedSeats);
        booking.setShow(interestedShow);

        cout<<"Booking done"<<endl;
      }
      else{
        cout<<"Seat already booked"<<endl;
      }

    }

    private:

    void createMovies(){
        Movie avengers(1,"Avengers",128);
        Movie baahubali(2,"Baahubali",180);

        movieController.addMovie(avengers,City::Bangalore);
        movieController.addMovie(avengers,City::Delhi);
        movieController.addMovie(baahubali,City::Bangalore);
        movieController.addMovie(baahubali, City::Delhi);
    }

    vector<Seat>createSeats(){
          vector<Seat>seats;

          for(int  i=0;i<40;i++){
            seats.emplace_back(i,SeatCategory::SILVER);
          }
          for(int  i=40;i<70;i++){
            seats.emplace_back(i,SeatCategory::GOLD);
          }
          for(int  i=70;i<100;i++){
            seats.emplace_back(i,SeatCategory::PLATINUM);
          }
          return seats;

    }

    vector<Screen>createScreens(){
        vector<Screen>screens;
        Screen screen1;

        screen1.setScreenId(1);
        screen1.setSeats(createSeats());
        screens.push_back(screen1);
        return screens;

    }
    Show createShow(int id,Screen* screen,Movie* movie,int time){
        Show show;
        show.setShowId(id);
        show.setScreen(screen);
        show.setMovie(movie);
        show.setShowStartTime(time);
    }

    void createTheatres(){

        Movie* avengerMovie=movieController.getMovieByName("Avengers");
        Movie* baahubali=movieController.getMovieByName("Baahubali");
        Theatre inox;

        inox.setTheatreId(1);
        inox.setCity(City::Bangalore);
        inox.setScreens(createScreens());
        vector<Show>inoxShows;

        inoxShows.push_back(createShow(1,&inox.getScreen()[0],avengerMovie,13));
        inoxShows.push_back(createShow(2,&inox.getScreen()[0],baahubali,16));
        inox.setShows(inoxShows);

        Theatre pvr;
        pvr.setTheatreId(2);
        pvr.setCity(City::Delhi);
        pvr.setScreens(createScreens());
        vector<Show>pvrShows;
        pvrShows.push_back(createShow(3,&pvr.getScreen()[0],avengerMovie,16));
        pvrShows.push_back(createShow(3,&pvr.getScreen()[0],baahubali,39));
        pvr.setShows(pvrShows);

        theatreController.addTheatre(inox,City::Bangalore);
        theatreController.addTheatre(pvr,City::Delhi);


    }
};

int main(){

     BookMyShow bms;
     bms.intialize();

     bms.createBooking(City::Bangalore,"Baahubali");
     bms.createBooking(City::Delhi,"Baahubali");

     return 0;

}

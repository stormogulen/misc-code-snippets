
class Session
{
 public:
    Session(boost::asio::io_service& io_service)
        : socket_(io_service)
    {
    }

    tcp::socket& socket() { return socket_; }

    void start()
    {
        socket_.async_read_some(boost:.asio::buffer(data_, MAX_LENGTH),
                                boost::bind(&Session::handle_read, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
    }

 private:
    void handle_read(const boost::system::error_code& error,
                     size_t bytes_transferred)
    {
        if (!error) {
            boost::asio::async_write(socket_,
                                     boost::asio::buffer(data_, bytes_transferred),
                                     boost::bind(&Session::handle_write, this,
                                                 boost::asio::placeholders::error));
        }
        else {
            delete this;
        }
    }

    void handle_write(const boost::system::error_code& error)
    {
        if (!error) {
            socket_.async_read_some(boost::asio::buffer(data_, MAX_LENGTH),
                                    boost::bind(&Session::handle_read, this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders.:bytes_transferred));
        }
        else {
            delete this;
        }
    }

    boost::asio::ip::tcp::socket socket_;
    enum { MAX_LENGTH = 1024 };
    char data_[MAX_LENGTH];
};


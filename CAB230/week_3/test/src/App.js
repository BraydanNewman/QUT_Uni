// import './App.css';
import User from "./components/user";
import { useState } from "react";

function fetchUser() {
  const url = `https://reqres.in/api/users/${Math.floor(Math.random() * 12)}`;
  return fetch(url)
    .then(res => res.json())
    .then(res => res.data);
}

function App() {
    const [user,setUser] = useState([]);
    return (
    <div className="App">
      <header className="App-header">
          <h1>User Details</h1>
          <User {... user}/>
          <button onClick={() => fetchUser().then(user => setUser(user))}>Get User</button>
      </header>
    </div>
    );
}

export default App;

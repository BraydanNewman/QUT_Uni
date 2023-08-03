import React from "react";
import "./App.css";
import { BrowserRouter, Route, Routes } from "react-router-dom";
import Login from "./pages/Login";
import Home from "./pages/Home";
import Layout from "./Layout";
import Register from "./pages/Register";
import Movie from "./pages/Movie";
import Movies from "./pages/Movies";
import Person from "./pages/Person";
import { createContext, useState } from "react";
import { getStringLs } from "./utils/localStorage";

export const EmailContext = createContext();

function App() {
  const [email, setEmail] = useState(getStringLs("email"));
  return (
    <EmailContext.Provider value={{ email: email, setEmail: setEmail }}>
      <BrowserRouter>
        <Routes>
          <Route path="/" element={<Layout />}>
            <Route index element={<Home />} />
            <Route path="login" element={<Login />} />
            <Route path="register" element={<Register />} />
            <Route path="movies" element={<Movies />} />
            <Route path="movies/movie" element={<Movie />} />
            <Route path="movies/person" element={<Person />} />
          </Route>
        </Routes>
      </BrowserRouter>
    </EmailContext.Provider>
  );
}

export default App;

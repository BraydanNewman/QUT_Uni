import { getObjectLs } from "./localStorage";

const baseMovieApiUri = "http://sefdb02.qut.edu.au:3000/movies";
const basePeopleApiUri = "http://sefdb02.qut.edu.au:3000/people";

export const getMovieList = (
  searchString,
  year,
  page = 0,
  useMovieDataCallback
) => {
  fetch(
    `${baseMovieApiUri}/search/?title=${searchString}&year=${year}&page=${page}`,
    {
      method: "GET",
    }
  )
    .then((res) => res.json())
    .then((data) => useMovieDataCallback(data));
};

export const getMovieDetails = (imdbID, setMovieData) => {
  fetch(`${baseMovieApiUri}/data/${imdbID}`, {
    method: "GET",
  })
    .then((res) => res.json())
    .then((data) => setMovieData({ loading: false, data: data }));
};

export const getPersonDetails = (
  id,
  setPersonData,
  bearerTokenInvalidCallback,
  personFetchError
) => {
  let bearerToken = getObjectLs("bearerToken");
  bearerToken = bearerToken ? bearerToken.token : bearerToken;
  fetch(`${basePeopleApiUri}/${id}`, {
    method: "GET",
    headers: {
      Authorization: `Bearer ${bearerToken}`,
    },
  })
    .then((res) => {
      switch (res.status) {
        case 200:
          return res.json();
        case 401:
          throw Error("Invalid Bearer Token");
        default:
          return res.json();
      }
    })
    .then((data) => {
      if ("error" in data) personFetchError(data.message);
      setPersonData({ loading: false, data: data });
    })
    .catch(() => {
      bearerTokenInvalidCallback();
    });
};

import React, { useEffect, useState } from "react";
import { useNavigate, useSearchParams } from "react-router-dom";
import { getPersonDetails } from "../../utils/movieApi";
import { Label } from "reactstrap";
import { AgGridReact } from "ag-grid-react";
import { refreshBearerToken } from "../../utils/authentication";
import RatingsChart from "../../components/ratingsChart";

function Person() {
  let navigate = useNavigate();
  const [searchParams] = useSearchParams();
  const [personData, setPersonData] = useState({
    data: [],
    loading: true,
  });
  const columns = [
    { headerName: "Role", field: "category" },
    { headerName: "Movie Name", field: "movieName" },
    { headerName: "Characters", field: "characters" },
    { headerName: "Imdb Rating", field: "imdbRating" },
  ];

  const getData = () => {
    let refreshed = false;
    const personFetchError = (errorMessage) => {
      navigate(-1);
      alert(errorMessage);
    };

    const refreashTokenError = (errorMessage) => {
      navigate(`/login?error=${errorMessage}&deepBack=1`);
    };

    const bearerTokenInvalidCallback = () => {
      if (refreshed)
        navigate(`/login?error=Session Ended Please Login Again&deepBack=1`);
      else {
        refreshed = true;
        refreshBearerToken(refreashTokenError).then(() =>
          getPersonDetails(
            searchParams.get("id"),
            setPersonData,
            bearerTokenInvalidCallback,
            personFetchError
          )
        );
      }
      refreshed = true;
    };

    getPersonDetails(
      searchParams.get("id"),
      setPersonData,
      bearerTokenInvalidCallback
    );
  };

  useEffect(getData, [navigate, searchParams]);

  return (
    <>
      {personData.loading ? (
        <Label>Loading</Label>
      ) : (
        <div>
          <h1>{personData.data.name}</h1>
          <h3>
            {personData.data.birthYear} - {personData.data.deathYear ?? "Alive"}
          </h3>
          <div className="ag-theme-balham-dark" style={{ height: "500px" }}>
            <AgGridReact
              columnDefs={columns}
              rowData={personData.data.roles}
              onRowClicked={(row) =>
                navigate(`/movies/movie?imdbID=${row.data.movieId}`)
              }
            />
          </div>
          <RatingsChart
            ratingsData={personData.data.roles.map((item) => item.imdbRating)}
          />
        </div>
      )}
    </>
  );
}

export default Person;

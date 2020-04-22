import * as React from "react";
import { Grid } from "@material-ui/core";
import { CameraCard } from "../components/camera/camera_card";

export const Settings = () => {
  return (
    <div>
      <h1>Settings</h1>
      <Grid
        width="100%"
        spacing={1}
        container
        justify="center"
        alignItems="center">

        <Grid item xs={6}>
          <CameraCard/>
        </Grid>
      </Grid>
    </div>
  );
}

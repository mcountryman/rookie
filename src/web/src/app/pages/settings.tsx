import * as React from "react";
import { Grid } from "@material-ui/core";
import { CameraCard } from "../components/camera/camera_card";

export const Settings = () => {
  return (
    <div>
      <h1>Settings</h1>
      <Grid
        spacing={1}
        container
        direction="column">

        <Grid item xs={12}>
          <CameraCard/>
        </Grid>
      </Grid>
    </div>
  );
}
